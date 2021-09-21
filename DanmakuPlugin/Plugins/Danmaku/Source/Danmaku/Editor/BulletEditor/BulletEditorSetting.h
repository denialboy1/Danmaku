// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BulletEditorSetting.generated.h"

/**
 * 
 */
UCLASS()
class DANMAKU_API UBulletEditorSetting : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float BulletSpawnPerSecond;

	UPROPERTY()
	AActor* Player;

	UPROPERTY()
	AActor* Enemy;

	UPROPERTY(EditAnywhere)
	FVector2D WallSize;

	UPROPERTY(EditAnywhere)
	float CameraDistance;

public:

	void SetBulletSpawnPerSecond(float InBulletSpawnPerSecond);
	float GetBulletSpawnPerSecond();

	void SetPlayer(AActor* InPlayer);
	AActor* GetPlayer();

	void SetEnemy(AActor* InEnemy);
	AActor* GetEnemy();

	void SetWallSize(FVector2D InWallSize);
	FVector2D GetWallSize();

	void SetCameraDistance(float InCameraDistance);
	float GetCameraDistance();

private:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;
#endif
};
