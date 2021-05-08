// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SCompoundWidget.h"
#include "GraphEditor.h"
#include "ContentBrowserDelegates.h"
/**
 * 
 */
class SBulletGraphEditor : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBulletGraphEditor) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TSharedPtr<SGraphEditor> GraphEditorPtr;

	class UBulletEdGraph* GraphObj;
};
