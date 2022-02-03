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

private:

	UPROPERTY()
	TArray<FBulletEditorBulletData> BulletDataArray;
public:
	void CreateData(FBulletEditorBulletData InBulletEditorBulletData = FBulletEditorBulletData())
	{
		BulletDataArray.Add(InBulletEditorBulletData);
	}

	int32 GetDataCount() { return BulletDataArray.Num(); }

	void AddBulletAttribute(int32 InIndex, FName InBulletAttributeName) { 
		if (BulletDataArray.IsValidIndex(InIndex))
		{
			BulletDataArray[InIndex].BulletAttributeList.Add(InBulletAttributeName);
		}
	}

	FBulletEditorBulletData GetBulletAttributeList(int32 InIndex) {
		if (BulletDataArray.IsValidIndex(InIndex))
		{
			return BulletDataArray[InIndex];
		}
		
		return FBulletEditorBulletData();
	}

};
