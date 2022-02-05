// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Danmaku/Editor/BulletEditor/BulletEditorBulletAttribute.h"
#include "BulletFactory.generated.h"

/**
 * 
 */
USTRUCT()
struct FBulletEditorBulletData
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FName> BulletAttributeList;
};


UCLASS(EditInlineNew)
class DANMAKU_API UBulletFactory : public UObject
{
	GENERATED_BODY()

public:
	TArray<FBulletEditorBulletData> GetBulletDataArray() { return BulletDataArray; }
	void SetBulletDataArray(TArray<FBulletEditorBulletData>& InBulletDataArray) { BulletDataArray = InBulletDataArray; }

private:
	UPROPERTY()
	TArray<FBulletEditorBulletData> BulletDataArray;

};
