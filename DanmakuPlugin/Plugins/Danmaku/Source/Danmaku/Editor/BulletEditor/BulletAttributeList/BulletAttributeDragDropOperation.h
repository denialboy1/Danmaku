// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Danmaku/Editor/BulletEditor/BulletEditorDefine.h"

#include "CoreMinimal.h"
#include "Input/DragAndDrop.h"


class FBulletAttributeDragDropOperation : public FDragDropOperation
{
public:
	DRAG_DROP_OPERATOR_TYPE(FBulletAttributeDragDropOperation, FDragDropOperation)
	
	virtual void OnDragged(const class FDragDropEvent& DragDropEvent) override;

	virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;

	static TSharedRef<FBulletAttributeDragDropOperation> CreateDragDropOperation(FBulletAttributeInfo InBulletAttributeInfo);

	FName GetAttributeName() const { return AttributeName; }

	EBulletAttributeType GetBulletAttributeType() const { return BulletAttributeType; }
private:
	FName AttributeName;

	EBulletAttributeType BulletAttributeType;
};
