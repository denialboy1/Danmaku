// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DanmakuPlugin/DanmakuPluginGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDanmakuPluginGameModeBase() {}
// Cross Module References
	DANMAKUPLUGIN_API UClass* Z_Construct_UClass_ADanmakuPluginGameModeBase_NoRegister();
	DANMAKUPLUGIN_API UClass* Z_Construct_UClass_ADanmakuPluginGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_DanmakuPlugin();
// End Cross Module References
	void ADanmakuPluginGameModeBase::StaticRegisterNativesADanmakuPluginGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_ADanmakuPluginGameModeBase_NoRegister()
	{
		return ADanmakuPluginGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ADanmakuPluginGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADanmakuPluginGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_DanmakuPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADanmakuPluginGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "DanmakuPluginGameModeBase.h" },
		{ "ModuleRelativePath", "DanmakuPluginGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADanmakuPluginGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADanmakuPluginGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADanmakuPluginGameModeBase_Statics::ClassParams = {
		&ADanmakuPluginGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ADanmakuPluginGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADanmakuPluginGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADanmakuPluginGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADanmakuPluginGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADanmakuPluginGameModeBase, 18111607);
	template<> DANMAKUPLUGIN_API UClass* StaticClass<ADanmakuPluginGameModeBase>()
	{
		return ADanmakuPluginGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADanmakuPluginGameModeBase(Z_Construct_UClass_ADanmakuPluginGameModeBase, &ADanmakuPluginGameModeBase::StaticClass, TEXT("/Script/DanmakuPlugin"), TEXT("ADanmakuPluginGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADanmakuPluginGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
