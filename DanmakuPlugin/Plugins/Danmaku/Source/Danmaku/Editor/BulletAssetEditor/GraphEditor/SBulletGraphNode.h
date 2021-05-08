// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"

class DANMAKU_API SBulletGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SBulletGraphNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, class UBulletEdGraphNode* InNode);

	virtual void UpdateGraphNode() override;
};
