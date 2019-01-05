// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Containers/StaticBitArray.h"
#include "IAnselPlugin.h"
#include "Camera/CameraTypes.h"
#include "Camera/CameraPhotography.h"
#include "Camera/PlayerCameraManager.h"
#include "HAL/ConsoleManager.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/ViewportSplitScreen.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/HUD.h"
#include "GameFramework/WorldSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/SWindow.h"
#include "Application/SlateApplicationBase.h"
#include <Runtime/ApplicationCore/Public/Windows/WindowsApplication.h>
#include "Runtime/Core/Public/Misc/OutputDeviceNull.h"
#include "AnselCaptureFunctionLibrary.h"
#include <AnselSDK.h>

DEFINE_LOG_CATEGORY_STATIC(LogAnselCapture, Log, All);

#define LOCTEXT_NAMESPACE "Photography"

/////////////////////////////////////////////////
// All the NVIDIA Ansel-specific details

class FNVAnselCaptureCameraPhotographyPrivate : public ICameraPhotography
{
public:
	FNVAnselCaptureCameraPhotographyPrivate();
	virtual ~FNVAnselCaptureCameraPhotographyPrivate() override;
	virtual bool UpdateCamera(FMinimalViewInfo& InOutPOV, APlayerCameraManager* PCMgr) override;
	virtual void UpdatePostProcessing(FPostProcessSettings& InOutPostProcessSettings) override;
	virtual void StartSession() override;
	virtual void StopSession() override;
	virtual bool IsSupported() override;
	virtual const TCHAR* const GetProviderName() override { return TEXT("NVIDIA Ansel Capture"); };

	virtual void SetUIControlVisibility(uint8 UIControlTarget, bool bIsVisible) override {}

	virtual void DefaultConstrainCamera(const FVector NewCameraLocation, const FVector PreviousCameraLocation, const FVector OriginalCameraLocation, FVector& OutCameraLocation, APlayerCameraManager* PCMgr) override
	{

	}

private:
	void ReconfigureAnsel();
	void DeconfigureAnsel();

	static ansel::StartSessionStatus AnselStartSessionCallback(ansel::SessionConfiguration& settings, void* userPointer);
	static void AnselStopSessionCallback(void* userPointer);
	static void AnselStartCaptureCallback(const ansel::CaptureConfiguration& CaptureInfo, void* userPointer);
	static void AnselStopCaptureCallback(void* userPointer);

	void AnselCameraToFMinimalView(FMinimalViewInfo& InOutPOV, ansel::Camera& AnselCam);
	void FMinimalViewToAnselCamera(ansel::Camera& InOutAnselCam, FMinimalViewInfo& POV);

	void SanitizePostprocessingForCapture(FPostProcessSettings& InOutPostProcessSettings);

	FMinimalViewInfo OriginalView;

	ansel::Configuration* AnselConfig;
	ansel::Camera AnselCamera;

	FPostProcessSettings UEPostProcessingOriginal;

	bool bAnselSessionStarted;
	bool bAnselSessionEnded;
	bool bAnselCaptureStarted;
	bool bAnselCaptureEnded;
	bool bAnselIsCapturing;
	bool bAnselSessionIsRunning;
	bool bTriggerNextTick;
	bool bTriggerNextCapture;
	ansel::CaptureConfiguration AnselCaptureInfo;


	bool bAutoPostprocess;

	/** Console variable delegate for checking when the console variables have changed */
	FConsoleCommandDelegate CVarDelegate;
	FConsoleVariableSinkHandle CVarDelegateHandle;
};

namespace AnselCapture
{
	void* AnselSDKDLLHandle = 0;
	bool bAnselDLLLoaded = false;
	bool bAnselHonourRoll = false;
	bool bAnselHonourPitch = false;
	FAnselCapturePauseDynamicDelegate PauseDelegate;
	FAnselCaptureUnpauseDynamicDelegate UnpauseDelegate;
}

FNVAnselCaptureCameraPhotographyPrivate::FNVAnselCaptureCameraPhotographyPrivate()
	: ICameraPhotography()
	, bAnselIsCapturing(false)
	, bAnselCaptureStarted(false)
	, bAnselCaptureEnded(false)
	, bAnselSessionStarted(false)
	, bAnselSessionEnded(false)
	, bTriggerNextCapture(false)
	, bTriggerNextTick(false)
	, bAnselSessionIsRunning(false)
{


	if (AnselCapture::bAnselDLLLoaded)
	{
		AnselConfig = new ansel::Configuration();

		CVarDelegate = FConsoleCommandDelegate::CreateLambda([this] {
			static float LastTranslationSpeed = -1.0f;
			static int32 LastSettleFrames = -1;

			static IConsoleVariable* CVarTranslationSpeed = IConsoleManager::Get().FindConsoleVariable(TEXT("r.Photography.TranslationSpeed"));
			static IConsoleVariable* CVarSettleFrames = IConsoleManager::Get().FindConsoleVariable(TEXT("r.Photography.SettleFrames"));

			float ThisTranslationSpeed = CVarTranslationSpeed->GetFloat();
			int32 ThisSettleFrames = CVarSettleFrames->GetInt();

			if (ThisTranslationSpeed != LastTranslationSpeed ||
				ThisSettleFrames != LastSettleFrames)
			{
				ReconfigureAnsel();
				LastTranslationSpeed = ThisTranslationSpeed;
				LastSettleFrames = ThisSettleFrames;
			}
		});

		CVarDelegateHandle = IConsoleManager::Get().RegisterConsoleVariableSink_Handle(CVarDelegate);
		ReconfigureAnsel();
	}
	else
	{
		UE_LOG(LogAnselCapture, Log, TEXT("Ansel DLL was not successfully loaded."));
	}
}


FNVAnselCaptureCameraPhotographyPrivate::~FNVAnselCaptureCameraPhotographyPrivate()
{
	if (AnselCapture::bAnselDLLLoaded)
	{
		IConsoleManager::Get().UnregisterConsoleVariableSink_Handle(CVarDelegateHandle);
		DeconfigureAnsel();
		delete AnselConfig;
	}
}

bool FNVAnselCaptureCameraPhotographyPrivate::IsSupported()
{
	return AnselCapture::bAnselDLLLoaded && ansel::isAnselAvailable();
}

void FNVAnselCaptureCameraPhotographyPrivate::AnselCameraToFMinimalView(FMinimalViewInfo& InOutPOV, ansel::Camera& AnselCam)
{
	InOutPOV.FOV = AnselCam.fov;
	InOutPOV.Location.X = AnselCam.position.x;
	InOutPOV.Location.Y = AnselCam.position.y;
	InOutPOV.Location.Z = AnselCam.position.z;
	FQuat rotq(AnselCam.rotation.x, AnselCam.rotation.y, AnselCam.rotation.z, AnselCam.rotation.w);
	InOutPOV.Rotation = FRotator(rotq);
	InOutPOV.OffCenterProjectionOffset.Set(AnselCam.projectionOffsetX, AnselCam.projectionOffsetY);
}

void FNVAnselCaptureCameraPhotographyPrivate::FMinimalViewToAnselCamera(ansel::Camera& InOutAnselCam, FMinimalViewInfo& POV)
{
	InOutAnselCam.fov = POV.FOV;
	InOutAnselCam.position = { POV.Location.X, POV.Location.Y, POV.Location.Z };
	FQuat rotq = POV.Rotation.Quaternion();
	InOutAnselCam.rotation = { rotq.X, rotq.Y, rotq.Z, rotq.W };
	InOutAnselCam.projectionOffsetX = 0.f; // Ansel only writes these, doesn't read
	InOutAnselCam.projectionOffsetY = 0.f;
}


bool FNVAnselCaptureCameraPhotographyPrivate::UpdateCamera(FMinimalViewInfo& InOutPOV, APlayerCameraManager* PCMgr)
{
	check(PCMgr != nullptr);

	APlayerController* PCOwner = PCMgr->GetOwningPlayerController();
	check(PCOwner != nullptr);

	// here a new frame is ready, we can brutally trigger a new capture
	// ensure to call it before the others !
	if (bTriggerNextTick)
	{
		OriginalView = InOutPOV;
		FMinimalViewToAnselCamera(AnselCamera, InOutPOV);
		ansel::updateCamera(AnselCamera);
		PCOwner->SetPause(true);
		AnselCapture::PauseDelegate.ExecuteIfBound();
		bTriggerNextCapture = true;
		bTriggerNextTick = false;
		return true;
	}



	// while capturing we simply call updateCamera()
	if (bAnselSessionIsRunning)
	{

		ansel::updateCamera(AnselCamera);
		AnselCameraToFMinimalView(InOutPOV, AnselCamera);

		// if honour roll is true, apply an additional rotation
		// obviously ensure the roll rotation is the first one
		if (AnselCapture::bAnselHonourRoll)
		{
			FQuat qrot = FQuat::MakeFromEuler(FVector(OriginalView.Rotation.GetComponentForAxis(EAxis::X), 0, 0)) * InOutPOV.Rotation.Quaternion();

			InOutPOV.Rotation = qrot.Rotator();
		}

		// same for pitch
		if (AnselCapture::bAnselHonourPitch)
		{
			FQuat qrot = FQuat::MakeFromEuler(FVector(0, OriginalView.Rotation.GetComponentForAxis(EAxis::Y), 0)) * InOutPOV.Rotation.Quaternion();

			InOutPOV.Rotation = qrot.Rotator();
		}

		// eliminate letterboxing during capture
		InOutPOV.bConstrainAspectRatio = false;
	}


	// first case, the Ansel session has been started
	// just pause the game
	if (bAnselSessionStarted)
	{
		bAnselSessionIsRunning = true;
		// pause the world, we will capture only "paused" frames
		PCOwner->SetPause(true);
		AnselCapture::PauseDelegate.ExecuteIfBound();

		// here we call updateCamera to setup the capturing stuff
		OriginalView = InOutPOV;
		FMinimalViewToAnselCamera(AnselCamera, InOutPOV);
		ansel::updateCamera(AnselCamera);

		bAnselSessionStarted = false;
		return false;
	}


	// session has ended, restore the world
	if (bAnselSessionEnded)
	{
		PCOwner->SetPause(false);
		AnselCapture::UnpauseDelegate.ExecuteIfBound();
		bAnselSessionEnded = false;
		bAnselSessionIsRunning = false;
		return false;
	}

	// we start capturing
	if (bAnselCaptureStarted)
	{
		bAnselIsCapturing = true;
		bAnselCaptureStarted = false;
		return false;
	}

	// when a frame is fully captured, we unpause the game,
	// we advance a frame, we restore the cursor and we trigger a new capture
	if (bAnselCaptureEnded)
	{
		bAnselIsCapturing = false;
		bAnselCaptureEnded = false;

		// Re-activate Windows Cursor as Ansel will automatically hide the Windows mouse cursor when Ansel UI is enabled.
		//	See https://nvidiagameworks.github.io/Ansel/md/Ansel_integration_guide.html
		// !Needs to be done after AnselStopSessionCallback
		TSharedPtr<GenericApplication> PlatformApplication = FSlateApplicationBase::Get().GetPlatformApplication();
		if (PlatformApplication.IsValid() && PlatformApplication->Cursor.IsValid())
		{
			PlatformApplication->Cursor->Show(PCOwner->ShouldShowMouseCursor());
		}
		PCOwner->SetPause(false);
		AnselCapture::UnpauseDelegate.ExecuteIfBound();
		bTriggerNextTick = true;
		return false;
	}


	// here we efectively start a new capture by brutally
	// simulating spacebar pressing/releasing
	if (bTriggerNextCapture)
	{
		INPUT SpaceBar = { 0 };
		SpaceBar.type = INPUT_KEYBOARD;
		SpaceBar.ki.wVk = VK_SPACE;
		SendInput(1, &SpaceBar, sizeof(INPUT));
		SpaceBar.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &SpaceBar, sizeof(INPUT));
		bTriggerNextCapture = false;
		return false;
	}


	return false;
}

void FNVAnselCaptureCameraPhotographyPrivate::SanitizePostprocessingForCapture(FPostProcessSettings& InOutPostProcessingSettings)
{
	if (bAnselIsCapturing)
	{
		if (bAutoPostprocess)
		{
			// force-disable the standard postprocessing effects which are known to
			// be problematic in multi-part shots

			// these effects tile poorly
			InOutPostProcessingSettings.bOverride_BloomDirtMaskIntensity = 1;
			InOutPostProcessingSettings.BloomDirtMaskIntensity = 0.f;
			InOutPostProcessingSettings.bOverride_LensFlareIntensity = 1;
			InOutPostProcessingSettings.LensFlareIntensity = 0.f;
			InOutPostProcessingSettings.bOverride_VignetteIntensity = 1;
			InOutPostProcessingSettings.VignetteIntensity = 0.f;
			InOutPostProcessingSettings.bOverride_SceneFringeIntensity = 1;
			InOutPostProcessingSettings.SceneFringeIntensity = 0.f;

			// freeze auto-exposure adaptation
			InOutPostProcessingSettings.bOverride_AutoExposureSpeedDown = 1;
			InOutPostProcessingSettings.AutoExposureSpeedDown = 0.f;
			InOutPostProcessingSettings.bOverride_AutoExposureSpeedUp = 1;
			InOutPostProcessingSettings.AutoExposureSpeedUp = 0.f;

			// bring rendering up to (at least) full resolution
			if (InOutPostProcessingSettings.ScreenPercentage < 100.f)
			{
				// note: won't override r.screenpercentage set from console, that takes precedence
				InOutPostProcessingSettings.bOverride_ScreenPercentage = 1;
				InOutPostProcessingSettings.ScreenPercentage = 100.f;
			}

			bool bAnselSuperresCaptureActive = AnselCaptureInfo.captureType == ansel::kCaptureTypeSuperResolution;
			bool bAnselStereoCaptureActive = AnselCaptureInfo.captureType == ansel::kCaptureType360Stereo || AnselCaptureInfo.captureType == ansel::kCaptureTypeStereo;

			if (bAnselStereoCaptureActive)
			{
				// Attempt to nerf DoF in stereoscopic shots where it can be quite unpleasant for the viewer
				InOutPostProcessingSettings.bOverride_DepthOfFieldScale = 1;
				InOutPostProcessingSettings.DepthOfFieldScale = 0.f; // BokehDOF
				InOutPostProcessingSettings.bOverride_DepthOfFieldNearBlurSize = 1;
				InOutPostProcessingSettings.DepthOfFieldNearBlurSize = 0.f; // GaussianDOF
				InOutPostProcessingSettings.bOverride_DepthOfFieldFarBlurSize = 1;
				InOutPostProcessingSettings.DepthOfFieldFarBlurSize = 0.f; // GaussianDOF
				InOutPostProcessingSettings.bOverride_DepthOfFieldDepthBlurRadius = 1;
				InOutPostProcessingSettings.DepthOfFieldDepthBlurRadius = 0.f; // CircleDOF
				InOutPostProcessingSettings.bOverride_DepthOfFieldVignetteSize = 1;
				InOutPostProcessingSettings.DepthOfFieldVignetteSize = 200.f; // Scene.h says 200.0 means 'no effect'
			}

			if (!bAnselSuperresCaptureActive)
			{
				// Disable SSR in multi-part shots unless taking a super-resolution shot; SSR *usually* degrades gracefully in tiled shots, and super-resolution mode in Ansel has an 'enhance' option which repairs any lingering SSR artifacts quite well.
				InOutPostProcessingSettings.bOverride_ScreenSpaceReflectionIntensity = 1;
				InOutPostProcessingSettings.ScreenSpaceReflectionIntensity = 0.f;
			}
		}
	}
}

void FNVAnselCaptureCameraPhotographyPrivate::UpdatePostProcessing(FPostProcessSettings& InOutPostProcessingSettings)
{
	if (bAnselIsCapturing)
	{
		SanitizePostprocessingForCapture(InOutPostProcessingSettings);
	}
}

void FNVAnselCaptureCameraPhotographyPrivate::StartSession()
{
	ansel::startSession();
}

void FNVAnselCaptureCameraPhotographyPrivate::StopSession()
{
	ansel::stopSession();
}

ansel::StartSessionStatus FNVAnselCaptureCameraPhotographyPrivate::AnselStartSessionCallback(ansel::SessionConfiguration& settings, void* userPointer)
{
	ansel::StartSessionStatus AnselSessionStatus = ansel::kDisallowed;
	FNVAnselCaptureCameraPhotographyPrivate* PrivateImpl = static_cast<FNVAnselCaptureCameraPhotographyPrivate*>(userPointer);
	check(PrivateImpl != nullptr);

	static IConsoleVariable* CVarAllow = IConsoleManager::Get().FindConsoleVariable(TEXT("r.Photography.Allow"));
	static IConsoleVariable* CVarEnableMultipart = IConsoleManager::Get().FindConsoleVariable(TEXT("r.Photography.EnableMultipart"));
	if (CVarAllow->GetInt() && !GIsEditor)
	{
		bool bEnableMultipart = !!CVarEnableMultipart->GetInt();

		settings.isTranslationAllowed = true;
		settings.isFovChangeAllowed = true;
		settings.isRotationAllowed = true;

		settings.isPauseAllowed = true;
		settings.isHighresAllowed = bEnableMultipart;
		settings.is360MonoAllowed = bEnableMultipart;
		settings.is360StereoAllowed = bEnableMultipart;

		PrivateImpl->bAnselSessionStarted = true;

		AnselSessionStatus = ansel::kAllowed;
	}

	UE_LOG(LogAnselCapture, Log, TEXT("Photography camera session attempt started, Allowed=%d"), int(AnselSessionStatus == ansel::kAllowed));

	return AnselSessionStatus;
}

void FNVAnselCaptureCameraPhotographyPrivate::AnselStopSessionCallback(void* userPointer)
{
	FNVAnselCaptureCameraPhotographyPrivate* PrivateImpl = static_cast<FNVAnselCaptureCameraPhotographyPrivate*>(userPointer);
	check(PrivateImpl != nullptr);
	PrivateImpl->bAnselSessionEnded = true;
	UE_LOG(LogAnselCapture, Log, TEXT("Photography camera session end"));
}

void FNVAnselCaptureCameraPhotographyPrivate::AnselStartCaptureCallback(const ansel::CaptureConfiguration& CaptureInfo, void* userPointer)
{
	FNVAnselCaptureCameraPhotographyPrivate* PrivateImpl = static_cast<FNVAnselCaptureCameraPhotographyPrivate*>(userPointer);
	check(PrivateImpl != nullptr);
	PrivateImpl->bAnselCaptureStarted = true;
	PrivateImpl->AnselCaptureInfo = CaptureInfo;

	UE_LOG(LogAnselCapture, Log, TEXT("Photography camera multi-part capture started"));
}

void FNVAnselCaptureCameraPhotographyPrivate::AnselStopCaptureCallback(void* userPointer)
{
	FNVAnselCaptureCameraPhotographyPrivate* PrivateImpl = static_cast<FNVAnselCaptureCameraPhotographyPrivate*>(userPointer);
	check(PrivateImpl != nullptr);
	PrivateImpl->bAnselCaptureEnded = true;
	UE_LOG(LogAnselCapture, Log, TEXT("Photography camera multi-part capture end"));
}

void FNVAnselCaptureCameraPhotographyPrivate::ReconfigureAnsel()
{
	check(AnselConfig != nullptr);
	AnselConfig->userPointer = this;
	AnselConfig->startSessionCallback = AnselStartSessionCallback;
	AnselConfig->stopSessionCallback = AnselStopSessionCallback;
	AnselConfig->startCaptureCallback = AnselStartCaptureCallback;
	AnselConfig->stopCaptureCallback = AnselStopCaptureCallback;

	AnselConfig->gameWindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
	UE_LOG(LogAnselCapture, Log, TEXT("gameWindowHandle= %p"), AnselConfig->gameWindowHandle);

	static IConsoleVariable* CVarTranslationSpeed = IConsoleManager::Get().FindConsoleVariable(TEXT("r.Photography.TranslationSpeed"));
	AnselConfig->translationalSpeedInWorldUnitsPerSecond = CVarTranslationSpeed->GetFloat();

	AnselConfig->metersInWorldUnit = 1.0f / 100.0f;
	AWorldSettings* WorldSettings = nullptr;
	if (GEngine->GetWorld() != nullptr)
	{
		WorldSettings = GEngine->GetWorld()->GetWorldSettings();
	}
	if (WorldSettings != nullptr && WorldSettings->WorldToMeters != 0.f)
	{
		AnselConfig->metersInWorldUnit = 1.0f / WorldSettings->WorldToMeters;
	}
	UE_LOG(LogAnselCapture, Log, TEXT("We reckon %f meters to 1 world unit"), AnselConfig->metersInWorldUnit);

	AnselConfig->isCameraOffcenteredProjectionSupported = true;

	AnselConfig->captureLatency = 0; // important

	static IConsoleVariable* CVarSettleFrames = IConsoleManager::Get().FindConsoleVariable(TEXT("r.Photography.SettleFrames"));
	AnselConfig->captureSettleLatency = CVarSettleFrames->GetInt();

	ansel::SetConfigurationStatus status = ansel::setConfiguration(*AnselConfig);
	if (status != ansel::kSetConfigurationSuccess)
	{
		UE_LOG(LogAnselCapture, Log, TEXT("ReconfigureAnsel setConfiguration returned %ld"), long int(status));
	}
}

void FNVAnselCaptureCameraPhotographyPrivate::DeconfigureAnsel()
{
	check(AnselConfig != nullptr);

	AnselConfig->userPointer = nullptr;
	AnselConfig->startSessionCallback = nullptr;
	AnselConfig->stopSessionCallback = nullptr;
	AnselConfig->startCaptureCallback = nullptr;
	AnselConfig->stopCaptureCallback = nullptr;
	AnselConfig->gameWindowHandle = nullptr;
	ansel::SetConfigurationStatus status = ansel::setConfiguration(*AnselConfig);
	if (status != ansel::kSetConfigurationSuccess)
	{
		UE_LOG(LogAnselCapture, Log, TEXT("DeconfigureAnsel setConfiguration returned %ld"), long int(status));
	}
}

class FAnselCaptureModule : public IAnselCaptureModule
{
public:
	virtual void StartupModule() override
	{
		ICameraPhotographyModule::StartupModule();
		check(!AnselCapture::bAnselDLLLoaded);

		// Late-load Ansel DLL.  DLL name has been worked out by the build scripts as ANSEL_DLL
		FString AnselDLLName;
		FString AnselBinariesRoot = FPaths::EngineDir() / TEXT("Plugins/Runtime/Nvidia/Ansel/Binaries/ThirdParty/");
		// common preprocessor fudge to convert macro expansion into string
#define STRINGIFY(X) STRINGIFY2(X)
#define STRINGIFY2(X) #X
		AnselDLLName = AnselBinariesRoot + TEXT(STRINGIFY(ANSEL_DLL));
		AnselCapture::AnselSDKDLLHandle = FPlatformProcess::GetDllHandle(*(AnselDLLName));

		AnselCapture::bAnselDLLLoaded = AnselCapture::AnselSDKDLLHandle != 0;
		UE_LOG(LogAnselCapture, Log, TEXT("Tried to load %s : success=%d"), *AnselDLLName, int(AnselCapture::bAnselDLLLoaded));
	}

	virtual void ShutdownModule() override
	{
		if (AnselCapture::bAnselDLLLoaded)
		{
			FPlatformProcess::FreeDllHandle(AnselCapture::AnselSDKDLLHandle);
			AnselCapture::AnselSDKDLLHandle = 0;
			AnselCapture::bAnselDLLLoaded = false;
		}
		ICameraPhotographyModule::ShutdownModule();
	}
private:

	virtual TSharedPtr< class ICameraPhotography > CreateCameraPhotography() override
	{
		TSharedPtr<ICameraPhotography> Photography = nullptr;

		FNVAnselCaptureCameraPhotographyPrivate* PhotographyPrivate = new FNVAnselCaptureCameraPhotographyPrivate();
		if (PhotographyPrivate->IsSupported())
		{
			Photography = TSharedPtr<ICameraPhotography>(PhotographyPrivate);
		}
		else
		{
			delete PhotographyPrivate;
		}

		return Photography;
	}
};

IMPLEMENT_MODULE(FAnselCaptureModule, AnselCapture)

#undef LOCTEXT_NAMESPACE