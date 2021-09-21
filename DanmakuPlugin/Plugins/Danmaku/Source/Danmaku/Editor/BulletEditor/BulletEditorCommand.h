// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "Danmaku/Editor/DanmakuStyle.h"
/**
 * 
 */
class FBulletEditorCommand : public TCommands<FBulletEditorCommand>
{
public:
	FBulletEditorCommand() : TCommands<FBulletEditorCommand>(
			TEXT("BulletEditor"),
			NSLOCTEXT("Contexts", "BulletEditor", "Danmaku Plugin"),
			NAME_None,
			FDanmakuStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> CommandShowBulletEditorSetting;
};
