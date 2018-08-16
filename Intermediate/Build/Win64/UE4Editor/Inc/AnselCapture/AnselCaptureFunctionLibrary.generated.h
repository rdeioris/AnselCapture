// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
#ifdef ANSELCAPTURE_AnselCaptureFunctionLibrary_generated_h
#error "AnselCaptureFunctionLibrary.generated.h already included, missing '#pragma once' in AnselCaptureFunctionLibrary.h"
#endif
#define ANSELCAPTURE_AnselCaptureFunctionLibrary_generated_h

#define Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execStopAnselCapture) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAnselCaptureFunctionLibrary::StopAnselCapture(Z_Param_WorldContextObject); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execStartAnselCapture) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAnselCaptureFunctionLibrary::StartAnselCapture(Z_Param_WorldContextObject); \
		P_NATIVE_END; \
	}


#define Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execStopAnselCapture) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAnselCaptureFunctionLibrary::StopAnselCapture(Z_Param_WorldContextObject); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execStartAnselCapture) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAnselCaptureFunctionLibrary::StartAnselCapture(Z_Param_WorldContextObject); \
		P_NATIVE_END; \
	}


#define Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAnselCaptureFunctionLibrary(); \
	friend struct Z_Construct_UClass_UAnselCaptureFunctionLibrary_Statics; \
public: \
	DECLARE_CLASS(UAnselCaptureFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AnselCapture"), NO_API) \
	DECLARE_SERIALIZER(UAnselCaptureFunctionLibrary)


#define Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_INCLASS \
private: \
	static void StaticRegisterNativesUAnselCaptureFunctionLibrary(); \
	friend struct Z_Construct_UClass_UAnselCaptureFunctionLibrary_Statics; \
public: \
	DECLARE_CLASS(UAnselCaptureFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AnselCapture"), NO_API) \
	DECLARE_SERIALIZER(UAnselCaptureFunctionLibrary)


#define Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAnselCaptureFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAnselCaptureFunctionLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAnselCaptureFunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAnselCaptureFunctionLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAnselCaptureFunctionLibrary(UAnselCaptureFunctionLibrary&&); \
	NO_API UAnselCaptureFunctionLibrary(const UAnselCaptureFunctionLibrary&); \
public:


#define Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAnselCaptureFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAnselCaptureFunctionLibrary(UAnselCaptureFunctionLibrary&&); \
	NO_API UAnselCaptureFunctionLibrary(const UAnselCaptureFunctionLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAnselCaptureFunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAnselCaptureFunctionLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAnselCaptureFunctionLibrary)


#define Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_PRIVATE_PROPERTY_OFFSET
#define Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_12_PROLOG
#define Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_PRIVATE_PROPERTY_OFFSET \
	Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_RPC_WRAPPERS \
	Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_INCLASS \
	Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_PRIVATE_PROPERTY_OFFSET \
	Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_INCLASS_NO_PURE_DECLS \
	Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Extreme_Raid_Plugins_AnselCapture_Source_AnselCapture_Public_AnselCaptureFunctionLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
