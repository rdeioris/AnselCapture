// Fill out your copyright notice in the Description page of Project Settings.

#include "AnselCaptureFunctionLibrary.h"
#include "Camera/CameraPhotography.h"


void UAnselCaptureFunctionLibrary::StartAnselCapture(UObject* WorldContextObject)
{
	FCameraPhotographyManager::Get().StartSession();
}

void UAnselCaptureFunctionLibrary::StopAnselCapture(UObject* WorldContextObject)
{
	FCameraPhotographyManager::Get().StopSession();
}

