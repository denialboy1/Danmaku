// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletMovementComponent.h"
#include "DirectionMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class DANMAKU_API UDirectionMovementComponent : public UBulletMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
