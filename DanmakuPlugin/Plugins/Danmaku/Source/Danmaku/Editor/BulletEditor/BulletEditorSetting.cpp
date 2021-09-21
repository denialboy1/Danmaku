// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletEditorSetting.h"
#include "BulletEditor.h"
#include "Danmaku/Editor/BulletEditor/ViewportEditor/BulletViewportTab.h"

void UBulletEditorSetting::SetBulletSpawnPerSecond(float InBulletSpawnPerSecond)
{
	BulletSpawnPerSecond = InBulletSpawnPerSecond;
}

float UBulletEditorSetting::GetBulletSpawnPerSecond()
{
	return BulletSpawnPerSecond;
}

void UBulletEditorSetting::SetPlayer(AActor* InPlayer)
{
	Player = InPlayer;
}

AActor* UBulletEditorSetting::GetPlayer()
{
	return Player;
}

void UBulletEditorSetting::SetEnemy(AActor* InEnemy)
{
	Enemy = InEnemy;
}

AActor* UBulletEditorSetting::GetEnemy()
{
	return Enemy;
}

void UBulletEditorSetting::SetWallSize(FVector2D InWallSize)
{
	WallSize = InWallSize;
}

FVector2D UBulletEditorSetting::GetWallSize()
{
	return WallSize;
}

void UBulletEditorSetting::SetCameraDistance(float InCameraDistance)
{
	CameraDistance = InCameraDistance;
}

float UBulletEditorSetting::GetCameraDistance()
{
	return CameraDistance;
}

void UBulletEditorSetting::PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent)
{
	if (InPropertyChangedEvent.GetPropertyName() == TEXT("CameraDistance"))
	{
		FBulletEditor::GetInstance()->GetBulletViewportTab()->SetOrthoZoom(CameraDistance);
	}
	else if (InPropertyChangedEvent.MemberProperty->GetName() == TEXT("WallSize"))
	{
		FBulletEditor::GetInstance()->GetBulletViewportTab()->UpdateWallSize();
	}
	
	Super::PostEditChangeProperty(InPropertyChangedEvent);
}
