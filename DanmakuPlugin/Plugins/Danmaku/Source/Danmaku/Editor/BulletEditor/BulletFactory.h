// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Danmaku/Editor/BulletEditor/BulletEditorBulletAttribute.h"
#include "BulletFactory.generated.h"

/**
 * 
 */
UCLASS()
class DANMAKU_API UBulletFactory : public UObject
{
	GENERATED_BODY()

private:
	TArray<FBulletEditorBulletAttribute> BulletAttributeList;


public:
	void AddAttribute(FBulletEditorBulletAttribute InBulletAttribute) { BulletAttributeList.Add(InBulletAttribute); }
	TArray<FBulletEditorBulletAttribute> GetBulletAttributeList() { return BulletAttributeList; }

};
