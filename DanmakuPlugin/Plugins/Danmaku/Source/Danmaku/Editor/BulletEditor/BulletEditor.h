// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Danmaku/Editor/BulletEditor/BulletAttributeList/BulletAttributeListTab.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/SBulletGraphTab.h"
#include "Editor/PropertyEditor/Public/PropertyEditorDelegates.h"

class IDetailsView;
class SDockableTab;

class FBulletEditor : public FAssetEditorToolkit
{
public:
	/** Destructor */
	virtual ~FBulletEditor();

	
#pragma region Editor
private:
	static const FName BulletEditorName;
	TArray<UObject*> EditingObjects;
	static TSharedPtr<FBulletEditor> BulletEditor;
private:
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit);
	void ExtendToolbar();
	void ShowBulletEditorSetting();
	/** Called when objects need to be swapped out for new versions, like after a blueprint recompile. */
	void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);
public:
	static TSharedRef<FBulletEditor> CreateEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit);
	static TSharedPtr<FBulletEditor> GetInstance();


	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
#pragma endregion

#pragma region Tab
public:
	/**	The tab ids for all the tabs used */
	static const FName BulletAttributeListTabId;
	static const FName BulletGraphEditorTabId;
	static const FName BulletViewportTabId;
	static const FName BulletDetailsTabId;

private:
	TSharedPtr<class SBulletViewportTab> BulletViewportTab;

public:
	TSharedPtr<class SBulletViewportTab> GetBulletViewportTab();
private:
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;

	TSharedRef<SDockTab> SpawnBulletAttributeListTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnBulletGraphEditorTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnBulletViewportTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnBulletDetailsTab(const FSpawnTabArgs& Args);

	
#pragma endregion

#pragma region DetailPanel
private:
	static TSharedPtr<IDetailsView> DetailView;
public:
	static void SetDetailViewObject(UObject* DetailViewObject);
private:
	UPROPERTY()
	static class UBulletEditorSetting* BulletEditorSetting;
public:
	//다른 액터를 하나로 모여서 보여주고 싶기 때문에 Setting을 모아서 값만 넣어줌.
	static class UBulletEditorSetting* GetBulletEditorSettingInstance();
#pragma endregion
};
