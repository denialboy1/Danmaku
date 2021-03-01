// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DanmakuPlugin/BulletMovementComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBulletMovementComponent() {}
// Cross Module References
	DANMAKUPLUGIN_API UClass* Z_Construct_UClass_UBulletMovementComponent_NoRegister();
	DANMAKUPLUGIN_API UClass* Z_Construct_UClass_UBulletMovementComponent();
	ENGINE_API UClass* Z_Construct_UClass_UMovementComponent();
	UPackage* Z_Construct_UPackage__Script_DanmakuPlugin();
// End Cross Module References
	void UBulletMovementComponent::StaticRegisterNativesUBulletMovementComponent()
	{
	}
	UClass* Z_Construct_UClass_UBulletMovementComponent_NoRegister()
	{
		return UBulletMovementComponent::StaticClass();
	}
	struct Z_Construct_UClass_UBulletMovementComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBulletMovementComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UMovementComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_DanmakuPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBulletMovementComponent_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "BulletMovementComponent.h" },
		{ "ModuleRelativePath", "BulletMovementComponent.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBulletMovementComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBulletMovementComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBulletMovementComponent_Statics::ClassParams = {
		&UBulletMovementComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UBulletMovementComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBulletMovementComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBulletMovementComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBulletMovementComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBulletMovementComponent, 1652583364);
	template<> DANMAKUPLUGIN_API UClass* StaticClass<UBulletMovementComponent>()
	{
		return UBulletMovementComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBulletMovementComponent(Z_Construct_UClass_UBulletMovementComponent, &UBulletMovementComponent::StaticClass, TEXT("/Script/DanmakuPlugin"), TEXT("UBulletMovementComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBulletMovementComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
