// Copyright Epic Games, Inc. All Rights Reserved.

#include "Danmaku.h"
#include "DanmakuStyle.h"
#include "DanmakuCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName DanmakuTabName("Danmaku");

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
}

TSharedRef<SDockTab> FDanmakuModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FDanmakuModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("Danmaku.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
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