// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AnselCaptureFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ANSELCAPTURE_API UAnselCaptureFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "Photography", meta = (WorldContext = WorldContextObject))
	static void StartAnselCapture(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Photography", meta = (WorldContext = WorldContextObject))
	static void StopAnselCapture(UObject* WorldContextObject);
	
	
};
