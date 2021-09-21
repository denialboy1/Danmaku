// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletEditorCommand.h"

#define LOCTEXT_NAMESPACE "BulletEditor"

void FBulletEditorCommand::RegisterCommands()
{
	UI_COMMAND(CommandShowBulletEditorSetting, "BulletEditorSetting", "Displays BulletEditorSetting", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE