// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Editor/PropertyEditor/Public/PropertyEditorDelegates.h"

class IDetailsView;
class SDockableTab;

class FBulletAssetEditor : public FAssetEditorToolkit
{
public:
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;


	/**
	 * Edits the specified asset object
	 *
	 * @param	Mode					Asset editing mode for this editor (standalone or world-centric)
	 * @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within
	 * @param	ObjectsToEdit			The object to edit
	 */
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit);

	/** Destructor */
	virtual ~FBulletAssetEditor();

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

private:
	/** Create the properties tab and its content */
	TSharedRef<SDockTab> SpawnMovementListTab(const FSpawnTabArgs& Args);

	TSharedRef<SDockTab> SpawnBulletActorTab(const FSpawnTabArgs& Args);

	TSharedRef<SDockTab> SpawnViewportTab(const FSpawnTabArgs& Args);

	TSharedRef<SDockTab> SpawnDetailTab(const FSpawnTabArgs& Args);


	/** Called when objects need to be swapped out for new versions, like after a blueprint recompile. */
	void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);

	/** Dockable tab for properties */
	TSharedPtr< SDockableTab > PropertiesTab;

	/** App Identifier. Technically, all simple editors are the same app, despite editing a variety of assets. */
	static const FName BulletEditorAppIdentifier;

	/**	The tab ids for all the tabs used */
	static const FName MovementListTabId;

	static const FName BulletActorTabId;

	static const FName ViewportTabId;

	static const FName DetailTabId;

	/** The objects open within this editor */
	TArray<UObject*> EditingObjects;

public:
	/** The name given to all instances of this type of editor */
	static const FName ToolkitFName; 

	static TSharedRef<FBulletAssetEditor> CreateEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit);
	
};
