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
	SLATE_ARGUMENT(UBulletFactory*, BulletFactory)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TSharedPtr<SGraphEditor> GraphEditorPtr;

	class UBulletEdGraph* GraphObj;

	UBulletFactory* BulletFactory;
public:
	UBulletEdGraph* GetBulletGraph() {return GraphObj;}
};
