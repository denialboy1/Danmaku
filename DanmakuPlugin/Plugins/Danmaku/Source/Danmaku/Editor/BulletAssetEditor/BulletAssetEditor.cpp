// Fill out your copyright notice in the Description page of Project Settings.

#include "Danmaku/Editor/BulletAssetEditor/BulletAssetEditor.h"
#include "Danmaku/Editor/BulletAssetEditor/GraphEditor/SBulletGraphTab.h"
#include "Danmaku/Editor/BulletAssetEditor/GraphEditor/BulletEdGraph.h"
#include "Danmaku/Editor/BulletAssetEditor/GraphEditor/BulletEdGraphNode.h"
#include "Danmaku/Editor/BulletAssetEditor/ViewportEditor/SBulletViewportTab.h"

#include "Modules/ModuleManager.h"
#include "EditorStyleSet.h"
#include "Widgets/Docking/SDockTab.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "Editor.h"
#include "Widgets/Input/SHyperlink.h"
#include "SourceCodeNavigation.h"
#include "Widgets/Layout/SUniformGridPanel.h"


#define LOCTEXT_NAMESPACE "BulletEditor"

const FName FBulletAssetEditor::ToolkitFName(TEXT("BulletEditor"));

TSharedPtr<FBulletAssetEditor> FBulletAssetEditor::BulletAssetEditor;

const FName FBulletAssetEditor::BulletEditorAppIdentifier(TEXT("BulletEditorApp"));
const FName FBulletAssetEditor::MovementListTabId(TEXT("MovementListTab"));
const FName FBulletAssetEditor::BulletActorTabId(TEXT("BulletActorTab"));
const FName FBulletAssetEditor::ViewportTabId(TEXT("ViewportTab"));
const FName FBulletAssetEditor::DetailTabId(TEXT("DetailTab"));

void FBulletAssetEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_BulletAssetEditor", "Asset Editor"));

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(MovementListTabId, FOnSpawnTab::CreateSP(this, &FBulletAssetEditor::SpawnMovementListTab))
		.SetDisplayName(LOCTEXT("MovementListTab", "MovementList"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	InTabManager->RegisterTabSpawner(BulletActorTabId, FOnSpawnTab::CreateSP(this, &FBulletAssetEditor::SpawnBulletActorTab))
		.SetDisplayName(LOCTEXT("BulletActorTab", "BulletActor"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	InTabManager->RegisterTabSpawner(ViewportTabId, FOnSpawnTab::CreateSP(this, &FBulletAssetEditor::SpawnViewportTab))
		.SetDisplayName(LOCTEXT("ViewportTab", "Viewport"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	InTabManager->RegisterTabSpawner(DetailTabId, FOnSpawnTab::CreateSP(this, &FBulletAssetEditor::SpawnDetailTab))
		.SetDisplayName(LOCTEXT("DetailTab", "Detail"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

TSharedRef<SDockTab> FBulletAssetEditor::SpawnMovementListTab(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == MovementListTabId);

	//데이터 추가
	TArray<FBulletAttributeInfoPtr> BulletAttributeList = {
		FBulletAttributeInfo::Make((TEXT("Direction"))),
		FBulletAttributeInfo::Make((TEXT("Rotation"))),
		FBulletAttributeInfo::Make((TEXT("Til"))),
		FBulletAttributeInfo::Make((TEXT("Direction")))
	};

	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("BulletEditor.Tabs.Properties"))
		.Label(LOCTEXT("BulletDetailsTitle", "Details"))
		.TabColorScale(GetTabColorScale())
		[
			SAssignNew(ListView, SBulletAttributeListWidget)
			.DataList(BulletAttributeList)
		];
}



TSharedRef<SDockTab> FBulletAssetEditor::SpawnBulletActorTab(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == BulletActorTabId);

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
				SAssignNew(BulletGraphTab, SBulletGraphTab)
			]
			
		];
}

TSharedRef<SDockTab> FBulletAssetEditor::SpawnViewportTab(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == ViewportTabId);

	return SNew(SDockTab)
		[
			SNew(SBulletViewportTab)
		];
}

TSharedRef<SDockTab> FBulletAssetEditor::SpawnDetailTab(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == DetailTabId);

	//디테일 패널 생성
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	if (DetailView == nullptr)
	{
		DetailView = PropertyEditorModule.CreateDetailView(FDetailsViewArgs());
	}

	return SNew(SDockTab)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				DetailView.ToSharedRef()
			]
		];
}

void FBulletAssetEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(MovementListTabId);
	InTabManager->UnregisterTabSpawner(BulletActorTabId);
	InTabManager->UnregisterTabSpawner(ViewportTabId);
	InTabManager->UnregisterTabSpawner(DetailTabId);
}

FBulletAssetEditor::~FBulletAssetEditor()
{
	GEditor->GetEditorSubsystem<UImportSubsystem>()->OnAssetPostImport.RemoveAll(this);
	GEditor->OnObjectsReplaced().RemoveAll(this);

	PropertiesTab.Reset();
}

FName FBulletAssetEditor::GetToolkitFName() const
{
	return ToolkitFName;
}

FText FBulletAssetEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Bullet Asset Editor");
}

FText FBulletAssetEditor::GetToolkitName() const
{
	const TArray<UObject*>& EditingObjs = GetEditingObjects();

	check(EditingObjs.Num() > 0);

	FFormatNamedArguments Args;
	Args.Add(TEXT("ToolkitName"), GetBaseToolkitName());

	if (EditingObjs.Num() == 1)
	{
		const UObject* EditingObject = EditingObjs[0];
		return FText::FromString(EditingObject->GetName());
	}
	else
	{
		UClass* SharedBaseClass = nullptr;
		for (int32 x = 0; x < EditingObjs.Num(); ++x)
		{
			UObject* Obj = EditingObjs[x];
			check(Obj);

			UClass* ObjClass = Cast<UClass>(Obj);
			if (ObjClass == nullptr)
			{
				ObjClass = Obj->GetClass();
			}
			check(ObjClass);

			// Initialize with the class of the first object we encounter.
			if (SharedBaseClass == nullptr)
			{
				SharedBaseClass = ObjClass;
			}

			// If we've encountered an object that's not a subclass of the current best baseclass,
			// climb up a step in the class hierarchy.
			while (!ObjClass->IsChildOf(SharedBaseClass))
			{
				SharedBaseClass = SharedBaseClass->GetSuperClass();
			}
		}

		check(SharedBaseClass);

		Args.Add(TEXT("NumberOfObjects"), EditingObjs.Num());
		Args.Add(TEXT("ClassName"), FText::FromString(SharedBaseClass->GetName()));
		return FText::Format(LOCTEXT("ToolkitTitle_EditingMultiple", "{NumberOfObjects} {ClassName} - {ToolkitName}"), Args);
	}
}

FText FBulletAssetEditor::GetToolkitToolTipText() const
{
	const TArray<UObject*>& EditingObjs = GetEditingObjects();

	check(EditingObjs.Num() > 0);

	FFormatNamedArguments Args;
	Args.Add(TEXT("ToolkitName"), GetBaseToolkitName());

	if (EditingObjs.Num() == 1)
	{
		const UObject* EditingObject = EditingObjs[0];
		return FAssetEditorToolkit::GetToolTipTextForObject(EditingObject);
	}
	else
	{
		UClass* SharedBaseClass = NULL;
		for (int32 x = 0; x < EditingObjs.Num(); ++x)
		{
			UObject* Obj = EditingObjs[x];
			check(Obj);

			UClass* ObjClass = Cast<UClass>(Obj);
			if (ObjClass == nullptr)
			{
				ObjClass = Obj->GetClass();
			}
			check(ObjClass);

			// Initialize with the class of the first object we encounter.
			if (SharedBaseClass == nullptr)
			{
				SharedBaseClass = ObjClass;
			}

			// If we've encountered an object that's not a subclass of the current best baseclass,
			// climb up a step in the class hierarchy.
			while (!ObjClass->IsChildOf(SharedBaseClass))
			{
				SharedBaseClass = SharedBaseClass->GetSuperClass();
			}
		}

		check(SharedBaseClass);

		Args.Add(TEXT("NumberOfObjects"), EditingObjs.Num());
		Args.Add(TEXT("ClassName"), FText::FromString(SharedBaseClass->GetName()));
		return FText::Format(LOCTEXT("ToolkitTitle_EditingMultipleToolTip", "{NumberOfObjects} {ClassName} - {ToolkitName}"), Args);
	}
}

FString FBulletAssetEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "Bullet Asset ").ToString();
}


FLinearColor FBulletAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.5f, 0.0f, 1.0f, 0.5f);
}




void FBulletAssetEditor::OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap)
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


TSharedRef<FBulletAssetEditor> FBulletAssetEditor::CreateEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit)
{
	if (BulletAssetEditor == nullptr)
	{
		BulletAssetEditor = MakeShareable(new FBulletAssetEditor);
		BulletAssetEditor->InitEditor(Mode, InitToolkitHost, ObjectsToEdit);
	}
	return BulletAssetEditor.ToSharedRef();
}

void FBulletAssetEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit)
{
	EditingObjects = ObjectsToEdit;
	GEditor->OnObjectsReplaced().AddSP(this, &FBulletAssetEditor::OnObjectsReplaced);

	//레이아웃 설정
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_BulletAssetEditor_Layout_v4")
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
					->AddTab(MovementListTabId, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.5f)
					->SetHideTabWell(true)
					->AddTab(BulletActorTabId, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(1.f)
					->SetHideTabWell(true)
					->AddTab(ViewportTabId, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.7f)
					->SetHideTabWell(true)
					->AddTab(DetailTabId, ETabState::OpenedTab)
				)
			)
		);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, FBulletAssetEditor::BulletEditorAppIdentifier, StandaloneDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, ObjectsToEdit);
}

#undef LOCTEXT_NAMESPACE
