// Fill out your copyright notice in the Description page of Project Settings.

#include "AnselCaptureFunctionLibrary.h"
#include "Camera/CameraPhotography.h"

namespace AnselCapture
{
	extern bool bAnselHonourRoll;
	extern bool bAnselHonourPitch;
}

void UAnselCaptureFunctionLibrary::StartAnselCapture(UObject* WorldContextObject, bool bHonourRoll, bool bHonourPitch)
{
	AnselCapture::bAnselHonourRoll = bHonourRoll;
	AnselCapture::bAnselHonourPitch = bHonourPitch;
	FCameraPhotographyManager::Get().StartSession();
}

void UAnselCaptureFunctionLibrary::StopAnselCapture(UObject* WorldContextObject)
{
	FCameraPhotographyManager::Get().StopSession();
}

