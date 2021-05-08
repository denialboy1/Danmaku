// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DanmakuStyle.h"

class FDanmakuCommands : public TCommands<FDanmakuCommands>
{
public:

	FDanmakuCommands()
		: TCommands<FDanmakuCommands>(TEXT("Danmaku"), NSLOCTEXT("Contexts", "Danmaku", "Danmaku Plugin"), NAME_None, FDanmakuStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};