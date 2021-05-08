// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

/**
 * 
 */

class FDanmakuEditorViewport : public FEditorViewportClient
{
public:
	FDanmakuEditorViewport(class ABullet* InCustomAsset, FPreviewScene& InPreviewScene);

	virtual void Tick(float DeltaSeconds) override;

public:
	class ABullet* CustomAsset;
};
