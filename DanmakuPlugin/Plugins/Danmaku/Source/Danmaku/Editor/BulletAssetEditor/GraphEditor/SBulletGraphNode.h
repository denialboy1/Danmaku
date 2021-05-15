// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"
#include "SBulletStackEntry.h"

class DANMAKU_API SBulletGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SBulletGraphNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, class UBulletEdGraphNode* InNode);

	//virtual void UpdateGraphNode() override;

	/** Create the inner node content area, including the left/right pin boxes */
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;

private:
	TSharedPtr<SBulletStackEntry> BulletStackEntry;
};
