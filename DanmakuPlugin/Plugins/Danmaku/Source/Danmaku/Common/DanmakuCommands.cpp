// Copyright Epic Games, Inc. All Rights Reserved.

#include "DanmakuCommands.h"

#define LOCTEXT_NAMESPACE "FDanmakuModule"

void FDanmakuCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Danmaku", "Bring up Danmaku window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
