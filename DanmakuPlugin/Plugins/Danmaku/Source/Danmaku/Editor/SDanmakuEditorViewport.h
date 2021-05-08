// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"
#include "Widgets/SCompoundWidget.h"
/**
 * 
 */
class SDanmakuEditorViewport : public SEditorViewport//public SCompoundWidget//: public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(SDanmakuEditorViewport) 
	{}
	//SLATE_ATTRIBUTE(FVector2D, ViewportSize);
	SLATE_END_ARGS()

	SDanmakuEditorViewport();
	~SDanmakuEditorViewport();

private:
	TSharedPtr<class FPreviewScene> PreviewScene;

public:
	void Construct(const FArguments& InArgs);

protected:
	/** Widget where the scene viewport is drawn in */
	//TSharedPtr<SViewport> ViewportWidget;
	//
	//TSharedPtr<SOverlay> ViewportOverlay;
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient();
};
