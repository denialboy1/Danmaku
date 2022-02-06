// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraphUtilities.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/SBulletGraphNode.h"
#include "Danmaku/Editor/BulletEditor/BulletEditorDefine.h"
#include "BulletEdGraphNode.generated.h"

/**
 * 
 */


UCLASS()
class DANMAKU_API UBulletEdGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	void AddMoveBulletAttribute(FName InAttributeName) { 
		FBulletAttributeInfo BulletAttributeInfo;
		BulletAttributeInfo.AttributeName = InAttributeName;
		BulletAttributeInfo.Guid = FGuid::NewGuid();

		MoveAttributeList.Add(BulletAttributeInfo);
	}

	void AddSpecialBulletAttribute(FName InAttributeName) {
		FBulletAttributeInfo BulletAttributeInfo;
		BulletAttributeInfo.AttributeName = InAttributeName;
		BulletAttributeInfo.Guid = FGuid::NewGuid();

		SpecialAttributeList.Add(BulletAttributeInfo);
	}

	TArray<FBulletAttributeInfo> GetMoveAttributeList() const { return MoveAttributeList; }
	TArray<FBulletAttributeInfo> GetSpecialAttributeList() const { return SpecialAttributeList; }

	void RemoveBulletAttribute(FGuid InGuid) { 
		for (int32 Index = 0; Index < MoveAttributeList.Num(); Index++)
		{
			if (MoveAttributeList[Index].Guid == InGuid)
			{
				MoveAttributeList.RemoveAt(Index);
				return;
			}
		}

		for (int32 Index = 0; Index < SpecialAttributeList.Num(); Index++)
		{
			if (SpecialAttributeList[Index].Guid == InGuid)
			{
				SpecialAttributeList.RemoveAt(Index);
				return;
			}
		}
	}

	void SetNodeIndex(int32 InIndex) { NodeIndex = InIndex; }
	int32 GetNodeIndex() { return NodeIndex; }
private:
	UPROPERTY(EditAnywhere, Category = "MoveAttributeList")
	TArray<FBulletAttributeInfo> MoveAttributeList;

	UPROPERTY(EditAnywhere, Category = "SpecialAttributeList")
	TArray<FBulletAttributeInfo> SpecialAttributeList;
	
	int32 NodeIndex;
};


class FBulletGraphNodeFactory : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override
	{
		if (UBulletEdGraphNode* BulletEdGraphNode = Cast<UBulletEdGraphNode>(Node))
		{
			BulletEdGraphNode->GetNodeIndex();
			return SNew(SBulletGraphNode)
				.BulletEdGraphNode(BulletEdGraphNode);
		}
		
		return nullptr;
	}
};

