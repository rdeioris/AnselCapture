// Fill out your copyright notice in the Description page of Project Settings.

#include "AnselCaptureFunctionLibrary.h"
#include "Camera/CameraPhotography.h"

extern bool bAnselHonourRoll;

void UAnselCaptureFunctionLibrary::StartAnselCapture(UObject* WorldContextObject, bool bHonourRoll)
{
	bAnselHonourRoll = bHonourRoll;
	FCameraPhotographyManager::Get().StartSession();
}

void UAnselCaptureFunctionLibrary::StopAnselCapture(UObject* WorldContextObject)
{
	FCameraPhotographyManager::Get().StopSession();
}

