// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AnselCaptureFunctionLibrary.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_DELEGATE(FAnselCapturePauseDynamicDelegate);
DECLARE_DYNAMIC_DELEGATE(FAnselCaptureUnpauseDynamicDelegate);


UCLASS()
class ANSELCAPTURE_API UAnselCaptureFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Photography", meta = (WorldContext = WorldContextObject, AutoCreateRefTerm="OnPause, OnUnpause"))
	static void StartAnselCapture(UObject* WorldContextObject, bool bHonourRoll, bool bHonourPitch, const FAnselCapturePauseDynamicDelegate& OnPause, const FAnselCaptureUnpauseDynamicDelegate& OnUnpause);

	UFUNCTION(BlueprintCallable, Category = "Photography", meta = (WorldContext = WorldContextObject))
	static void StopAnselCapture(UObject* WorldContextObject);
	
	
};
