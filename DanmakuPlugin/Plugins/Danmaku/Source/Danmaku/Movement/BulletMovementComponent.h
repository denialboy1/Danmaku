// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "BulletMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class DANMAKU_API UBulletMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Angle;
	
	UPROPERTY(EditAnywhere)
	float AngleAccelation;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float SpeedAccelation;

};