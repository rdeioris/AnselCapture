// Fill out your copyright notice in the Description page of Project Settings.

#include "AnselCaptureFunctionLibrary.h"
#include "Runtime/CoreUObject/Public/UObject/WeakObjectPtr.h"
#include "Camera/CameraPhotography.h"

namespace AnselCapture
{
	extern bool bAnselHonourRoll;
	extern bool bAnselHonourPitch;
	extern FAnselCapturePauseDynamicDelegate PauseDelegate;
	extern FAnselCaptureUnpauseDynamicDelegate UnpauseDelegate;
}

void UAnselCaptureFunctionLibrary::StartAnselCapture(UObject* WorldContextObject, bool bHonourRoll, bool bHonourPitch, const FAnselCapturePauseDynamicDelegate& OnPause, const FAnselCaptureUnpauseDynamicDelegate& OnUnpause)
{
	AnselCapture::bAnselHonourRoll = bHonourRoll;
	AnselCapture::bAnselHonourPitch = bHonourPitch;
	AnselCapture::PauseDelegate = OnPause;
	AnselCapture::UnpauseDelegate = OnUnpause;
	FCameraPhotographyManager::Get().StartSession();
}

void UAnselCaptureFunctionLibrary::StopAnselCapture(UObject* WorldContextObject)
{
	FCameraPhotographyManager::Get().StopSession();
}

