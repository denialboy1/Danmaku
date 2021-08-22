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

class FBulletGraphNodeFactory : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override
	{
		if (UBulletEdGraphNode* BulletEdGraphNode = Cast<UBulletEdGraphNode>(Node))
		{
			return SNew(SBulletGraphNode, BulletEdGraphNode);
		}

		return nullptr;
	}
};

UCLASS()
class DANMAKU_API UBulletEdGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	void AddBulletAttribute(FName AttributeName);
	TArray<FName> GetBulletAttributeList() const { return BulletAttributeList; }
private:
	//���⿡ ����Ʈ ������ ������
	UPROPERTY(EditAnywhere, Category = "BulletAttributeList")
	TArray<FName> BulletAttributeList;

};
