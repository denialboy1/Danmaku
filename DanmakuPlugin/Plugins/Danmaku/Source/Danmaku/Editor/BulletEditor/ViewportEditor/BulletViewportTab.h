// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletEditorViewportWidget.h"
#include "Widgets/SCompoundWidget.h"
/**
 * 
 */
class DANMAKU_API SBulletViewportTab : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBulletViewportTab) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

private:
	FReply OnPlayButtonClicked();
	FReply OnStopButtonClicked();
	FReply OnPauseButtonClicked();

private:
	TSharedPtr<SBulletEditorViewport> BulletEditorViewportPtr;

};
