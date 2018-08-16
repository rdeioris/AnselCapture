// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnselCapture/Public/AnselCaptureFunctionLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnselCaptureFunctionLibrary() {}
// Cross Module References
	ANSELCAPTURE_API UClass* Z_Construct_UClass_UAnselCaptureFunctionLibrary_NoRegister();
	ANSELCAPTURE_API UClass* Z_Construct_UClass_UAnselCaptureFunctionLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_AnselCapture();
	ANSELCAPTURE_API UFunction* Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	ANSELCAPTURE_API UFunction* Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture();
// End Cross Module References
	void UAnselCaptureFunctionLibrary::StaticRegisterNativesUAnselCaptureFunctionLibrary()
	{
		UClass* Class = UAnselCaptureFunctionLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "StartAnselCapture", &UAnselCaptureFunctionLibrary::execStartAnselCapture },
			{ "StopAnselCapture", &UAnselCaptureFunctionLibrary::execStopAnselCapture },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture_Statics
	{
		struct AnselCaptureFunctionLibrary_eventStartAnselCapture_Parms
		{
			UObject* WorldContextObject;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture_Statics::NewProp_WorldContextObject = { UE4CodeGen_Private::EPropertyClass::Object, "WorldContextObject", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AnselCaptureFunctionLibrary_eventStartAnselCapture_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture_Statics::NewProp_WorldContextObject,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture_Statics::Function_MetaDataParams[] = {
		{ "Category", "Photography" },
		{ "ModuleRelativePath", "Public/AnselCaptureFunctionLibrary.h" },
		{ "WorldContext", "WorldContextObject" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAnselCaptureFunctionLibrary, "StartAnselCapture", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04042401, sizeof(AnselCaptureFunctionLibrary_eventStartAnselCapture_Parms), Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture_Statics
	{
		struct AnselCaptureFunctionLibrary_eventStopAnselCapture_Parms
		{
			UObject* WorldContextObject;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture_Statics::NewProp_WorldContextObject = { UE4CodeGen_Private::EPropertyClass::Object, "WorldContextObject", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(AnselCaptureFunctionLibrary_eventStopAnselCapture_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture_Statics::NewProp_WorldContextObject,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture_Statics::Function_MetaDataParams[] = {
		{ "Category", "Photography" },
		{ "ModuleRelativePath", "Public/AnselCaptureFunctionLibrary.h" },
		{ "WorldContext", "WorldContextObject" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAnselCaptureFunctionLibrary, "StopAnselCapture", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04042401, sizeof(AnselCaptureFunctionLibrary_eventStopAnselCapture_Parms), Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAnselCaptureFunctionLibrary_NoRegister()
	{
		return UAnselCaptureFunctionLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UAnselCaptureFunctionLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAnselCaptureFunctionLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_AnselCapture,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAnselCaptureFunctionLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StartAnselCapture, "StartAnselCapture" }, // 3905371277
		{ &Z_Construct_UFunction_UAnselCaptureFunctionLibrary_StopAnselCapture, "StopAnselCapture" }, // 3861935198
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAnselCaptureFunctionLibrary_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "AnselCaptureFunctionLibrary.h" },
		{ "ModuleRelativePath", "Public/AnselCaptureFunctionLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAnselCaptureFunctionLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAnselCaptureFunctionLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAnselCaptureFunctionLibrary_Statics::ClassParams = {
		&UAnselCaptureFunctionLibrary::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x001000A0u,
		FuncInfo, ARRAY_COUNT(FuncInfo),
		nullptr, 0,
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_UAnselCaptureFunctionLibrary_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UAnselCaptureFunctionLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAnselCaptureFunctionLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAnselCaptureFunctionLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAnselCaptureFunctionLibrary, 3612142033);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAnselCaptureFunctionLibrary(Z_Construct_UClass_UAnselCaptureFunctionLibrary, &UAnselCaptureFunctionLibrary::StaticClass, TEXT("/Script/AnselCapture"), TEXT("UAnselCaptureFunctionLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAnselCaptureFunctionLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
