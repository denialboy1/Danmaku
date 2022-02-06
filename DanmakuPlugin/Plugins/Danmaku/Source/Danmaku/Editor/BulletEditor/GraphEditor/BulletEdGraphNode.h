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
	
	void AddBulletAttribute(FName InAttributeName) { 
		FBulletAttributeInfo BulletAttributeInfo;
		BulletAttributeInfo.AttributeName = InAttributeName;
		BulletAttributeInfo.Guid = FGuid::NewGuid();

		BulletAttributeList.Add(BulletAttributeInfo);
	}

	TArray<FBulletAttributeInfo> GetBulletAttributeList() const { return BulletAttributeList; }
	void RemoveBulletAttribute(FGuid InGuid) { 
		for (int32 Index = 0; Index < BulletAttributeList.Num(); Index++)
		{
			if (BulletAttributeList[Index].Guid == InGuid)
			{
				BulletAttributeList.RemoveAt(Index);
				break;
			}
		}
	}
	void SetNodeIndex(int32 InIndex) { NodeIndex = InIndex; }
	int32 GetNodeIndex() { return NodeIndex; }
private:
	//여기에 리스트 정보가 들어가야함
	UPROPERTY(EditAnywhere, Category = "MoveAttributeList")
		TArray<FBulletAttributeInfo> BulletAttributeList;

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

