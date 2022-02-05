// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraphUtilities.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/SBulletGraphNode.h"
#include "BulletEdGraphNode.generated.h"

/**
 * 
 */
USTRUCT()
struct FBulletAttributeInfo
{
	GENERATED_BODY()

	FGuid Guid;

	UPROPERTY()
	FName AttributeName;
};

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
	//���⿡ ����Ʈ ������ ������
	UPROPERTY(EditAnywhere, Category = "BulletAttributeList")
	TArray<FBulletAttributeInfo> BulletAttributeList;

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

