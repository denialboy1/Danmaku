// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletEditorDefine.generated.h"

UENUM()
enum class EMoveAttributeList : uint8
{
	Direction,
	Spiral,
	Wave,
	Cycloid,
	Vortex,
	Orbit,
};

UENUM()
enum class ESpecialAttributeList : uint8
{
	Pierce,
	Reflection,
	Homing,
	AroundWall,
	Returning,
	Plasma,
	Time
};

USTRUCT()
struct FBulletAttributeInfo
{
	GENERATED_BODY()

		FGuid Guid;

	UPROPERTY()
		FName AttributeName;
};

USTRUCT()
struct FBulletData
{
	GENERATED_BODY()

		UPROPERTY()
		TArray<FName> BulletAttributeList;
};
