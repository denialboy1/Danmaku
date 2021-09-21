// Copyright Epic Games, Inc. All Rights Reserved.

#include "Danmaku.h"

#include "Danmaku/Editor/DanmakuDetails.h"
#include "Danmaku/Editor/SDanmakuEditorViewport.h"
#include "Danmaku/Editor/BulletEditor/BulletAssetActions.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/BulletEdGraphNode.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/BulletGraphEditorDetailCustomization.h"
#include "Danmaku/Editor/BulletEditor/BulletEditorDetailCustomization.h"

#include "Danmaku/Actor/DanmakuBullet/DanmakuBullet.h"


#include "DanmakuStyle.h"
#include "DanmakuCommands.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "AssetToolsModule.h"
#include "EdGraphUtilities.h"



//#include "Danmaku/Editor/BulletAsset.h"
#include "PropertyEditorDelegates.h"
#include "PropertyEditorModule.h"
#include "BulletEditor/BulletEditorCommand.h"


static const FName BulletEdGraphNodeCustomizationName("BulletEdGraphNode");
static const FName BulletEditorCustomizationName("BulletEditorSetting");


#define LOCTEXT_NAMESPACE "FDanmakuModule"

void FDanmakuModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FDanmakuStyle::Initialize();
	FDanmakuStyle::ReloadTextures();

	FDanmakuCommands::Register();
	FBulletEditorCommand::Register();

	PluginCommands = MakeShareable(new FUICommandList);
	
	

	// register custom types:
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		// add custom category
		EAssetTypeCategories::Type DanmakuCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Danmaku")), FText::FromString("Danmaku"));
		// register our custom asset with example category
		TSharedPtr<IAssetTypeActions> Action = MakeShareable(new FBulletAssetActions(DanmakuCategory));
		AssetTools.RegisterAssetTypeActions(Action.ToSharedRef());
		// saved it here for unregister later
		CreatedAssetTypeActions.Add(Action);
	}


	//자신이 커스텀한 디테일 패널 등록 
	FPropertyEditorModule& PropertyModule =	FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	//PropertyModule.RegisterCustomClassLayout("Bullet", FOnGetDetailCustomizationInstance::CreateStatic(&MyCustomization::MakeInsance));
	PropertyModule.RegisterCustomClassLayout(BulletEdGraphNodeCustomizationName, FOnGetDetailCustomizationInstance::CreateStatic(&BulletGraphEditorDetailCustomization::MakeInstance));
	PropertyModule.RegisterCustomClassLayout(BulletEditorCustomizationName, FOnGetDetailCustomizationInstance::CreateStatic(&BulletEditorDetailCustomization::MakeInstance, BulletEditorDetailCustomization::EActorType::GAMESETTING));
	
	//PropertyModule.RegisterCustomClassLayout("DanmakuActor", FOnGetDetailCustomizationInstance::CreateStatic(&MyCustomization::MakeInsance));

	PropertyModule.NotifyCustomizationModuleChanged();

	//EdGraph를 정상적으로 호출하기 위해 등록
	BulletGraphNodeFactory = MakeShareable(new FBulletGraphNodeFactory());
	if (BulletGraphNodeFactory)
	{
		FEdGraphUtilities::RegisterVisualNodeFactory(BulletGraphNodeFactory);
	}
	
}

void FDanmakuModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FDanmakuStyle::Shutdown();

	FDanmakuCommands::Unregister();

	FBulletEditorCommand::Unregister();

	FCoreDelegates::OnPostEngineInit.RemoveAll(this);

	// Unregister all the asset types that we registered
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 i = 0; i < CreatedAssetTypeActions.Num(); ++i)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[i].ToSharedRef());
		}
	}
	CreatedAssetTypeActions.Empty();


	// unregister custom layouts
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout(BulletEdGraphNodeCustomizationName);
		PropertyModule.UnregisterCustomClassLayout(BulletEditorCustomizationName);
	}

	//unregister EdGraphNode
	if (BulletGraphNodeFactory)
	{
		FEdGraphUtilities::UnregisterVisualNodeFactory(BulletGraphNodeFactory);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDanmakuModule, Danmaku)