// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SCompoundWidget.h"
#include "GraphEditor.h"
#include "Danmaku/Editor/BulletEditor/BulletFactory.h"
#include "ContentBrowserDelegates.h"
/**
 * 
 */
class SBulletGraphTab : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBulletGraphTab) {}
	SLATE_ARGUMENT(TArray<FBulletEditorBulletData>, BulletDataArray)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	class UBulletEdGraph* GetBulletEdGraph() { return BulletEdGraph; }
private:
	class UBulletEdGraph* BulletEdGraph;

	TSharedPtr<SGraphEditor> GraphEditorPtr;
};
