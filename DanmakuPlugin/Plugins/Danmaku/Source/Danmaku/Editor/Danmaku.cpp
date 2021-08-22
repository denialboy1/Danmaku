// Copyright Epic Games, Inc. All Rights Reserved.

#include "Danmaku.h"

#include "Danmaku/Editor/DanmakuDetails.h"
#include "Danmaku/Editor/SDanmakuEditorViewport.h"
#include "Danmaku/Editor/BulletEditor/BulletAssetActions.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/BulletEdGraphNode.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/BulletGraphEditorDetailCustomization.h"
#include "Danmaku/Editor/BulletEditor/ViewportEditor/BulletViewportEditorDetailCustomization.h"

#include "Danmaku/Actor/Bullet/Bullet.h"


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


static const FName DanmakuTabName("Danmaku");
static const FName BulletEdGraphNodeCustomizationName("BulletEdGraphNode");
static const FName BulletActorCustomizationName("BulletActor");


#define LOCTEXT_NAMESPACE "FDanmakuModule"

void FDanmakuModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FDanmakuStyle::Initialize();
	FDanmakuStyle::ReloadTextures();

	FDanmakuCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FDanmakuCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FDanmakuModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDanmakuModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(DanmakuTabName, FOnSpawnTab::CreateRaw(this, &FDanmakuModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FDanmakuTabTitle", "Danmaku"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);


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
	PropertyModule.RegisterCustomClassLayout(BulletActorCustomizationName, FOnGetDetailCustomizationInstance::CreateStatic(&BulletViewportEditorDetailCustomization::MakeInstance));
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

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DanmakuTabName);

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
		PropertyModule.UnregisterCustomClassLayout(BulletActorCustomizationName);
	}

	//unregister EdGraphNode
	if (BulletGraphNodeFactory)
	{
		FEdGraphUtilities::UnregisterVisualNodeFactory(BulletGraphNodeFactory);
	}


}

TSharedRef<SDockTab> FDanmakuModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FDanmakuModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("Danmaku.cpp"))
		);

	//여기서는 총알 및 패턴 리스트를 볼수 있는 에디터 생성.

	return SNew(SDockTab)
		.TabRole(ETabRole::MajorTab)
		[
			// Put your tab content here!
				SNew(SUniformGridPanel)
				+ SUniformGridPanel::Slot(0, 0)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SDanmakuEditorViewport)
		]
			
		];
}

void FDanmakuModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(DanmakuTabName);
}


void FDanmakuModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FDanmakuCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDanmakuCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDanmakuModule, Danmaku)