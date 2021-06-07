// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletViewportTab.h"
#include "SBulletEditorViewport.h"
#include "Danmaku/Editor/DanmakuStyle.h"


#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SSpacer.h"



void SBulletViewportTab::Construct(const FArguments& Args)
{
	TSharedPtr<FButtonStyle> PlayButtonStyle = MakeShareable(new FButtonStyle);
	PlayButtonStyle->SetNormal(*(FDanmakuStyle::PlayButtonNormalInstance->GetBrush(TEXT("BulletAssetEditor.PlayButton.Normal"))));
	PlayButtonStyle->SetHovered(*(FDanmakuStyle::PlayButtonHorveredInstance->GetBrush(TEXT("BulletAssetEditor.PlayButton.Horvered"))));
	PlayButtonStyle->SetPressed(*(FDanmakuStyle::PlayButtonPressedInstance->GetBrush(TEXT("BulletAssetEditor.PlayButton.Pressed"))));

	TSharedPtr<FButtonStyle> StopButtonStyle = MakeShareable(new FButtonStyle);
	StopButtonStyle->SetNormal(*(FDanmakuStyle::StopButtonNormalInstance->GetBrush(TEXT("BulletAssetEditor.StopButton.Normal"))));
	StopButtonStyle->SetHovered(*(FDanmakuStyle::StopButtonHorveredInstance->GetBrush(TEXT("BulletAssetEditor.StopButton.Horvered"))));
	StopButtonStyle->SetPressed(*(FDanmakuStyle::StopButtonPressedInstance->GetBrush(TEXT("BulletAssetEditor.StopButton.Pressed"))));

	TSharedPtr<FButtonStyle> PauseButtonStyle = MakeShareable(new FButtonStyle);
	PauseButtonStyle->SetNormal(*(FDanmakuStyle::PauseButtonNormalInstance->GetBrush(TEXT("BulletAssetEditor.PauseButton.Normal"))));
	PauseButtonStyle->SetHovered(*(FDanmakuStyle::PauseButtonHorveredInstance->GetBrush(TEXT("BulletAssetEditor.PauseButton.Horvered"))));
	PauseButtonStyle->SetPressed(*(FDanmakuStyle::PauseButtonPressedInstance->GetBrush(TEXT("BulletAssetEditor.PauseButton.Pressed"))));

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
			]
		]
	+ SHorizontalBox::Slot()
		[
			SNew(SBorder)
		[
			SNew(SButton)
			.ButtonStyle(StopButtonStyle.Get())
		]
		]
	+ SHorizontalBox::Slot()
		[
			SNew(SBorder)
		[
			SNew(SButton)
			.ButtonStyle(PauseButtonStyle.Get())
		]
		]
		]
	+ SVerticalBox::Slot()
		[
			SNew(SBulletEditorViewport)
		]
	];
}
