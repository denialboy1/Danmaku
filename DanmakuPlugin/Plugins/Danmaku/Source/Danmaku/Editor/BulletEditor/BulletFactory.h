// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Danmaku/Editor/BulletEditor/BulletEditorBulletAttribute.h"
#include "BulletEditorDefine.h"
#include "BulletFactory.generated.h"

/**
 * 
 */


UCLASS(EditInlineNew)
class DANMAKU_API UBulletFactory : public UObject
{
	GENERATED_BODY()

public:
	TArray<FBulletData> GetBulletDataArray() { return BulletDataArray; }
	void SetBulletDataArray(TArray<FBulletData>& InBulletDataArray) { BulletDataArray = InBulletDataArray; }

private:
	UPROPERTY()
	TArray<FBulletData> BulletDataArray;

};
