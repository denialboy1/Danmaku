// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"
#include "SBulletStackEntry.h"

class DANMAKU_API SBulletGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SBulletGraphNode) {}
	SLATE_ARGUMENT(class UBulletEdGraphNode*, BulletEdGraphNode)
	SLATE_END_ARGS()


	void Construct(const FArguments& InArgs);

	virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	/** Create the inner node content area, including the left/right pin boxes */
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;

	void AddBulletAttribute(FName AttributeName);
private:
	TSharedPtr<SBulletStackEntry> BulletStackEntry;
};
