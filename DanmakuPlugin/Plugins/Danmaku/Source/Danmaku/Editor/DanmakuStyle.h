// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"


/* 탄막 관련된 이미지는 한곳에서 여기 한곳에 몰아서 보관 */
class FDanmakuStyle
{
public:
	static void Initialize();
	static void Shutdown();
	/** reloads textures used by slate renderer */
	static void ReloadTextures();

	static FName GetStyleSetName();
private:
	static TSharedRef< class FSlateStyleSet > Create(FString StyleName, FString PropertyName, FString ImageName, FVector2D ImageSize);
	static TSharedRef< class FSlateStyleSet > Create(FString StyleName, FString PropertyName, FString ImageName, FVector2D ImageSize, FLinearColor LineColor);
public:
	static TSharedPtr< class FSlateStyleSet > PlayButtonNormalInstance;
	static TSharedPtr< class FSlateStyleSet > PlayButtonHorveredInstance;
	static TSharedPtr< class FSlateStyleSet > PlayButtonPressedInstance;

	static TSharedPtr< class FSlateStyleSet > PlayingButtonInstance;

	static TSharedPtr< class FSlateStyleSet > StopButtonNormalInstance;
	static TSharedPtr< class FSlateStyleSet > StopButtonHorveredInstance;
	static TSharedPtr< class FSlateStyleSet > StopButtonPressedInstance;

	static TSharedPtr< class FSlateStyleSet > PauseButtonNormalInstance;
	static TSharedPtr< class FSlateStyleSet > PauseButtonHorveredInstance;
	static TSharedPtr< class FSlateStyleSet > PauseButtonPressedInstance;
};