// Copyright Epic Games, Inc. All Rights Reserved.

#include "DanmakuStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr< class FSlateStyleSet > FDanmakuStyle::PlayButtonNormalInstance = nullptr;
TSharedPtr< class FSlateStyleSet > FDanmakuStyle::PlayButtonHorveredInstance = nullptr;
TSharedPtr< class FSlateStyleSet > FDanmakuStyle::PlayButtonPressedInstance = nullptr;
TSharedPtr< class FSlateStyleSet > FDanmakuStyle::StopButtonNormalInstance = nullptr;
TSharedPtr< class FSlateStyleSet > FDanmakuStyle::StopButtonHorveredInstance = nullptr;
TSharedPtr< class FSlateStyleSet > FDanmakuStyle::StopButtonPressedInstance = nullptr;
TSharedPtr< class FSlateStyleSet > FDanmakuStyle::PauseButtonNormalInstance = nullptr;
TSharedPtr< class FSlateStyleSet > FDanmakuStyle::PauseButtonHorveredInstance = nullptr;
TSharedPtr< class FSlateStyleSet > FDanmakuStyle::PauseButtonPressedInstance = nullptr;
TSharedPtr< class FSlateStyleSet > FDanmakuStyle::PlayingButtonInstance = nullptr;

#define REGISTER_SLATE_STYLE(Instance, StyleName, PropertyName, ImageName, ImageSize, ...) \
if (Instance == nullptr) \
{ \
	Instance = Create(StyleName, PropertyName, ImageName, ImageSize, __VA_ARGS__); \
	FSlateStyleRegistry::RegisterSlateStyle(*Instance); \
}

#define UNREGISTER_SLATE_STYLE(Instance) \
if (Instance) \
{ \
	FSlateStyleRegistry::UnRegisterSlateStyle(*Instance); \
	ensure(Instance.IsUnique()); \
	Instance.Reset(); \
}

void FDanmakuStyle::Initialize()
{
	REGISTER_SLATE_STYLE(PlayButtonNormalInstance, TEXT("PlayButton.Normal"), TEXT("BulletAssetEditor.PlayButton.Normal"), TEXT("PlayButton"), FVector2D(30, 30), FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
	REGISTER_SLATE_STYLE(PlayButtonHorveredInstance, TEXT("PlayButton.Horvered"), TEXT("BulletAssetEditor.PlayButton.Horvered"), TEXT("PlayButton"), FVector2D(30, 30), FLinearColor(0.5f,0.5f,0.5f,1.0f));
	REGISTER_SLATE_STYLE(PlayButtonPressedInstance, TEXT("PlayButton.Pressed"), TEXT("BulletAssetEditor.PlayButton.Pressed"), TEXT("PlayButton"), FVector2D(30, 30), FLinearColor(0.05f, 0.05f, 0.05f, 1.0f));
	REGISTER_SLATE_STYLE(StopButtonNormalInstance, TEXT("StopButton.Normal"), TEXT("BulletAssetEditor.StopButton.Normal"), TEXT("StopButton"), FVector2D(30, 30), FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
	REGISTER_SLATE_STYLE(StopButtonHorveredInstance, TEXT("StopButton.Horvered"), TEXT("BulletAssetEditor.StopButton.Horvered"), TEXT("StopButton"), FVector2D(30, 30), FLinearColor(0.5f, 0.5f, 0.5f, 1.0f));
	REGISTER_SLATE_STYLE(StopButtonPressedInstance, TEXT("StopButton.Pressed"), TEXT("BulletAssetEditor.StopButton.Pressed"), TEXT("StopButton"), FVector2D(30, 30), FLinearColor(0.05f, 0.05f, 0.05f, 1.0f));
	REGISTER_SLATE_STYLE(PauseButtonNormalInstance, TEXT("PauseButton.Normal"), TEXT("BulletAssetEditor.PauseButton.Normal"), TEXT("PauseButton"), FVector2D(30, 30), FLinearColor(0.3f, 0.3f, 0.3f, 1.0f));
	REGISTER_SLATE_STYLE(PauseButtonHorveredInstance, TEXT("PauseButton.Horvered"), TEXT("BulletAssetEditor.PauseButton.Horvered"), TEXT("PauseButton"), FVector2D(30, 30), FLinearColor(0.5f, 0.5f, 0.5f, 1.0f));
	REGISTER_SLATE_STYLE(PauseButtonPressedInstance, TEXT("PauseButton.Pressed"), TEXT("BulletAssetEditor.PauseButton.Pressed"), TEXT("PauseButton"), FVector2D(30, 30), FLinearColor(0.05f, 0.05f, 0.05f, 1.0f));
	REGISTER_SLATE_STYLE(PlayButtonPressedInstance, TEXT("PlayingButton"), TEXT("BulletAssetEditor.PlayingButton"), TEXT("PlayingButton"), FVector2D(30, 30));
}



void FDanmakuStyle::Shutdown()
{
	UNREGISTER_SLATE_STYLE(PlayButtonNormalInstance);
	UNREGISTER_SLATE_STYLE(PlayButtonHorveredInstance);
	UNREGISTER_SLATE_STYLE(PlayButtonPressedInstance);
	UNREGISTER_SLATE_STYLE(StopButtonNormalInstance);
	UNREGISTER_SLATE_STYLE(StopButtonHorveredInstance);
	UNREGISTER_SLATE_STYLE(StopButtonPressedInstance);
	UNREGISTER_SLATE_STYLE(PauseButtonNormalInstance);
	UNREGISTER_SLATE_STYLE(PauseButtonHorveredInstance);
	UNREGISTER_SLATE_STYLE(PauseButtonPressedInstance);
	UNREGISTER_SLATE_STYLE(PlayButtonPressedInstance);
}

FName FDanmakuStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("DanmakuStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef< class FSlateStyleSet > FDanmakuStyle::Create(FString StyleName, FString PropertyName, FString ImageName, FVector2D ImageSize)
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet(*StyleName));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("Danmaku")->GetBaseDir() / TEXT("Resources"));
	Style->Set(*PropertyName, new IMAGE_BRUSH(*ImageName, ImageSize));
	return Style;
}

TSharedRef< class FSlateStyleSet > FDanmakuStyle::Create(FString StyleName, FString PropertyName, FString ImageName, FVector2D ImageSize, FLinearColor LineColor)
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet(*StyleName));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("Danmaku")->GetBaseDir() / TEXT("Resources"));
	Style->Set(*PropertyName, new IMAGE_BRUSH(*ImageName, ImageSize, LineColor));
	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FDanmakuStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}
