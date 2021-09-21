// Fill out your copyright notice in the Description page of Project Settings.

#include "Danmaku/Editor/BulletEditor/BulletEditor.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/SBulletGraphTab.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/BulletEdGraph.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/BulletEdGraphNode.h"
#include "Danmaku/Editor/BulletEditor/ViewportEditor/BulletViewportTab.h"
#include "BulletEditorSetting.h"
#include "BulletEditorCommand.h"
#include "BulletEditorDetailCustomization.h"

#define LOCTEXT_NAMESPACE "BulletEditor"

//TSharedPtr<FBulletEditor> FBulletEditor::BulletEditor;
const FName FBulletEditor::BulletEditorName(TEXT("BulletEditor"));
const FName FBulletEditor::BulletAttributeListTabId(TEXT("BulletAttributeListTabId"));
const FName FBulletEditor::BulletGraphEditorTabId(TEXT("BulletGraphEditorTabId"));
const FName FBulletEditor::BulletViewportTabId(TEXT("BulletViewportTabId"));
const FName FBulletEditor::BulletDetailsTabId(TEXT("BulletDetailsTabId"));

TSharedPtr<FBulletEditor> FBulletEditor::BulletEditor;
TSharedPtr<IDetailsView> FBulletEditor::DetailView;
UBulletEditorSetting* FBulletEditor::BulletEditorSetting;

FBulletEditor::~FBulletEditor()
{
	GEditor->GetEditorSubsystem<UImportSubsystem>()->OnAssetPostImport.RemoveAll(this);
	GEditor->OnObjectsReplaced().RemoveAll(this);
}

FName FBulletEditor::GetToolkitFName() const
{
	return BulletEditorName;
}

FText FBulletEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Bullet Asset Editor");
}

FString FBulletEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "Bullet Asset ").ToString();
}


FLinearColor FBulletEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.5f, 0.0f, 1.0f, 0.5f);
}



TSharedRef<FBulletEditor> FBulletEditor::CreateEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit)
{
	TSharedRef< FBulletEditor > NewEditor(new FBulletEditor());
	BulletEditor = NewEditor;

	NewEditor->InitEditor(Mode, InitToolkitHost, ObjectsToEdit);

	return NewEditor;
}


TSharedPtr<FBulletEditor> FBulletEditor::GetInstance()
{
	if (BulletEditor == nullptr)
	{
		return TSharedRef<FBulletEditor>(new FBulletEditor());
	}
	return BulletEditor;
}

void FBulletEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit)
{
	EditingObjects = ObjectsToEdit;
	GEditor->OnObjectsReplaced().AddSP(this, &FBulletEditor::OnObjectsReplaced);

	//레이아웃 설정
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_BulletEditor_Layout_v4")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.5f)
					->SetHideTabWell(true)
					->AddTab(BulletAttributeListTabId, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.5f)
					->SetHideTabWell(true)
					->AddTab(BulletGraphEditorTabId, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(1.f)
					->SetHideTabWell(true)
					->AddTab(BulletViewportTabId, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.7f)
					->SetHideTabWell(true)
					->AddTab(BulletDetailsTabId, ETabState::OpenedTab)
				)
			)
		);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;

	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, FBulletEditor::BulletEditorName, StandaloneDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, ObjectsToEdit);

	ExtendToolbar();
}

void FBulletEditor::ExtendToolbar()
{
	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

	struct Local
	{
		static void FillToolbar(FToolBarBuilder& ToolbarBuilder)
		{
			const FBulletEditorCommand& BulletEditorCommands = FBulletEditorCommand::Get();

			ToolbarBuilder.BeginSection("Command");
			ToolbarBuilder.AddToolBarButton(BulletEditorCommands.CommandShowBulletEditorSetting);
			ToolbarBuilder.EndSection();
		}
	};

	ToolbarExtender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		/*ViewportPtr->GetCommandList()*/ GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateStatic(&Local::FillToolbar)
	);

	GetToolkitCommands()->MapAction(FBulletEditorCommand::Get().CommandShowBulletEditorSetting, FExecuteAction::CreateSP(this, &FBulletEditor::ShowBulletEditorSetting), FCanExecuteAction());

	AddToolbarExtender(ToolbarExtender);
	RegenerateMenusAndToolbars();
}

void FBulletEditor::ShowBulletEditorSetting()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.RegisterCustomClassLayout(TEXT("BulletEditorSetting"), FOnGetDetailCustomizationInstance::CreateStatic(&BulletEditorDetailCustomization::MakeInstance, BulletEditorDetailCustomization::EActorType::GAMESETTING));
	SetDetailViewObject(BulletEditorSetting);
}

void FBulletEditor::OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap)
{
	bool bChangedAny = false;

	// Refresh our details view if one of the objects replaced was in the map. This gets called before the reinstance GC fixup, so we might as well fixup EditingObjects now too
	for (int32 i = 0; i < EditingObjects.Num(); i++)
	{
		UObject* SourceObject = EditingObjects[i];
		UObject* ReplacedObject = ReplacementMap.FindRef(SourceObject);

		if (ReplacedObject && ReplacedObject != SourceObject)
		{
			EditingObjects[i] = ReplacedObject;
			bChangedAny = true;
		}
	}
}

TSharedPtr<class SBulletViewportTab> FBulletEditor::GetBulletViewportTab()
{
	if (BulletViewportTab == nullptr)
	{
		BulletViewportTab = SNew(SBulletViewportTab);
	}

	return BulletViewportTab;
}

void FBulletEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_BulletEditor", "Asset Editor"));
	
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	
	InTabManager->RegisterTabSpawner(BulletAttributeListTabId, FOnSpawnTab::CreateSP(this, &FBulletEditor::SpawnBulletAttributeListTab))
		.SetDisplayName(FText::FromName(BulletAttributeListTabId))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	InTabManager->RegisterTabSpawner(BulletGraphEditorTabId, FOnSpawnTab::CreateSP(this, &FBulletEditor::SpawnBulletGraphEditorTab))
		.SetDisplayName(FText::FromName(BulletGraphEditorTabId))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	InTabManager->RegisterTabSpawner(BulletViewportTabId, FOnSpawnTab::CreateSP(this, &FBulletEditor::SpawnBulletViewportTab))
		.SetDisplayName(FText::FromName(BulletViewportTabId))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	InTabManager->RegisterTabSpawner(BulletDetailsTabId, FOnSpawnTab::CreateSP(this, &FBulletEditor::SpawnBulletDetailsTab))
		.SetDisplayName(FText::FromName(BulletDetailsTabId))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FBulletEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(BulletAttributeListTabId);
	InTabManager->UnregisterTabSpawner(BulletGraphEditorTabId);
	InTabManager->UnregisterTabSpawner(BulletViewportTabId);
	InTabManager->UnregisterTabSpawner(BulletDetailsTabId);
}

TSharedRef<SDockTab> FBulletEditor::SpawnBulletAttributeListTab(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == BulletAttributeListTabId);

	//데이터 추가
	TArray<FBulletAttributePtr> BulletMovementAttributePtrList = { 
		MakeShareable(new FBulletAttribute(TEXT("Direction"))),
		MakeShareable(new FBulletAttribute(TEXT("Spiral"))),
		MakeShareable(new FBulletAttribute(TEXT("Wave"))),
		MakeShareable(new FBulletAttribute(TEXT("Cycloid"))),
		MakeShareable(new FBulletAttribute(TEXT("Vortex"))),
		MakeShareable(new FBulletAttribute(TEXT("Orbit")))
	};

	TArray<FBulletAttributePtr> BulletAttributePtrList = {
		MakeShareable(new FBulletAttribute(TEXT("Pierce"))),
		MakeShareable(new FBulletAttribute(TEXT("Reflection"))),
		MakeShareable(new FBulletAttribute(TEXT("Homing"))),
		MakeShareable(new FBulletAttribute(TEXT("AroundWall"))),
		MakeShareable(new FBulletAttribute(TEXT("Returning"))),
		MakeShareable(new FBulletAttribute(TEXT("Plasma"))),
		MakeShareable(new FBulletAttribute(TEXT("Time"))),
	};


	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("BulletEditor.Tabs.Properties"))
		.Label(LOCTEXT("BulletDetailsTitle", "Details"))
		.TabColorScale(GetTabColorScale())
		[
			SNew(SBulletAttributeListTab)
			.BulletAttributePtrList(BulletAttributePtrList)
			.BulletMovementAttributePtrList(BulletMovementAttributePtrList)
		];
}



TSharedRef<SDockTab> FBulletEditor::SpawnBulletGraphEditorTab(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == BulletGraphEditorTabId);

	return SNew(SDockTab)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		     .FillHeight(0.1f)
			[
				SNew(STextBlock)
				.Text(FText::FromString("ActorName"))
			]
			+ SVerticalBox::Slot()
			[
				SNew(SBulletGraphTab)
			]
			
		];
}

TSharedRef<SDockTab> FBulletEditor::SpawnBulletViewportTab(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == BulletViewportTabId);

	return SNew(SDockTab)
		[
			SAssignNew(BulletViewportTab, SBulletViewportTab)
		];
}

TSharedRef<SDockTab> FBulletEditor::SpawnBulletDetailsTab(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == BulletDetailsTabId);

	//디테일 패널 생성
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	DetailView = PropertyEditorModule.CreateDetailView(FDetailsViewArgs());

	return SNew(SDockTab)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				DetailView.ToSharedRef()
			]
		];
}

void FBulletEditor::SetDetailViewObject(UObject* DetailViewObject)
{
	if (DetailView)
	{
		DetailView->SetObject(DetailViewObject);
		DetailView->ForceRefresh();
	}
}

UBulletEditorSetting* FBulletEditor::GetBulletEditorSettingInstance()
{
	if (BulletEditorSetting == nullptr)
	{
		BulletEditorSetting = NewObject<UBulletEditorSetting>();
		BulletEditorSetting->SetBulletSpawnPerSecond(1.0f);
		BulletEditorSetting->AddToRoot();
	}

	return BulletEditorSetting;
}

#undef LOCTEXT_NAMESPACE
