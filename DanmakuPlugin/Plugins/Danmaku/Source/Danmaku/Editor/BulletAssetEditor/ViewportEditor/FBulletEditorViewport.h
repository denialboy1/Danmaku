// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"


class FBulletEditorViewport : public FEditorViewportClient
{
public:
	FBulletEditorViewport(FPreviewScene* InPreviewScene);
public:
	class AActor* Enemy;
	class AActor* Bullet;
};
