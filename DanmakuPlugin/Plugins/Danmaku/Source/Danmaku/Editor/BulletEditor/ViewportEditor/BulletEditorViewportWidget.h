// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"
#include "BulletEditorViewport.h"

class DANMAKU_API SBulletEditorViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(SBulletEditorViewport) {}
	SLATE_END_ARGS();
public:
	void Construct(const FArguments& InArgs);

	void PlaySimulation();
	void StopSimulation();
	void PauseSimulation();

protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient();
	virtual void OnFocusViewportToSelection() override;
	virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;
private:
	TSharedPtr<class FPreviewScene> PreviewScene;
	TSharedPtr<FBulletEditorViewport> EditorViewportClient;
};
