// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletViewportTab.h"
#include "Danmaku/Editor/DanmakuStyle.h"
#include "Widgets/Input/SButton.h"

void SBulletViewportTab::Construct(const FArguments& Args)
{
	TSharedPtr<FButtonStyle> PlayButtonStyle = MakeShareable(new FButtonStyle);
	PlayButtonStyle->SetNormal(*(FDanmakuStyle::PlayButtonNormalInstance->GetBrush(TEXT("BulletEditor.PlayButton.Normal"))));
	PlayButtonStyle->SetHovered(*(FDanmakuStyle::PlayButtonHorveredInstance->GetBrush(TEXT("BulletEditor.PlayButton.Horvered"))));
	PlayButtonStyle->SetPressed(*(FDanmakuStyle::PlayButtonPressedInstance->GetBrush(TEXT("BulletEditor.PlayButton.Pressed"))));

	TSharedPtr<FButtonStyle> StopButtonStyle = MakeShareable(new FButtonStyle);
	StopButtonStyle->SetNormal(*(FDanmakuStyle::StopButtonNormalInstance->GetBrush(TEXT("BulletEditor.StopButton.Normal"))));
	StopButtonStyle->SetHovered(*(FDanmakuStyle::StopButtonHorveredInstance->GetBrush(TEXT("BulletEditor.StopButton.Horvered"))));
	StopButtonStyle->SetPressed(*(FDanmakuStyle::StopButtonPressedInstance->GetBrush(TEXT("BulletEditor.StopButton.Pressed"))));

	TSharedPtr<FButtonStyle> PauseButtonStyle = MakeShareable(new FButtonStyle);
	PauseButtonStyle->SetNormal(*(FDanmakuStyle::PauseButtonNormalInstance->GetBrush(TEXT("BulletEditor.PauseButton.Normal"))));
	PauseButtonStyle->SetHovered(*(FDanmakuStyle::PauseButtonHorveredInstance->GetBrush(TEXT("BulletEditor.PauseButton.Horvered"))));
	PauseButtonStyle->SetPressed(*(FDanmakuStyle::PauseButtonPressedInstance->GetBrush(TEXT("BulletEditor.PauseButton.Pressed"))));

	

	this->ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.FillHeight(0.03f)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()

		[
			SNew(SBorder)
			[
				SNew(SButton)
				.ButtonStyle(PlayButtonStyle.Get())
				.OnClicked(this, &SBulletViewportTab::OnPlayButtonClicked)

			]
		]
	+ SHorizontalBox::Slot()
		[
			SNew(SBorder)
		[
			SNew(SButton)
			.ButtonStyle(StopButtonStyle.Get())
			.OnClicked(this, &SBulletViewportTab::OnStopButtonClicked)
		]
		]
	+ SHorizontalBox::Slot()
		[
			SNew(SBorder)
			[
				SNew(SButton)
				.ButtonStyle(PauseButtonStyle.Get())
				.OnClicked(this, &SBulletViewportTab::OnPauseButtonClicked)
			]
		]
		]
	+ SVerticalBox::Slot()
		[
			SAssignNew(BulletEditorViewportPtr, SBulletEditorViewport)
		]
	];
}

FReply SBulletViewportTab::OnPlayButtonClicked()
{
	if (BulletEditorViewportPtr)
	{
		BulletEditorViewportPtr->PlaySimulation();
		return FReply::Handled();
	}
	
	return FReply::Unhandled();
}

FReply SBulletViewportTab::OnStopButtonClicked()
{
	if (BulletEditorViewportPtr)
	{
		BulletEditorViewportPtr->StopSimulation();
		return FReply::Handled();
	}
	
	return FReply::Unhandled();
}

FReply SBulletViewportTab::OnPauseButtonClicked()
{
	if (BulletEditorViewportPtr)
	{
		BulletEditorViewportPtr->PauseSimulation();
		return FReply::Handled();
	}

	return FReply::Unhandled();
}
