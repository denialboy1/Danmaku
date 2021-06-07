// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class DANMAKU_API SBulletEditorViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(SBulletEditorViewport) {}
	SLATE_END_ARGS();
public:
	void Construct(const FArguments& InArgs);
protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient();

private:
	TSharedPtr<class FPreviewScene> PreviewScene;
};
