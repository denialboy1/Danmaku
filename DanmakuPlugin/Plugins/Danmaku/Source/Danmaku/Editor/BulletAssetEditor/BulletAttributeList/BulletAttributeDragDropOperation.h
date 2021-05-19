// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/DragAndDrop.h"

class FBulletAttributeDragDropOperation : public FDragDropOperation
{
public:
	DRAG_DROP_OPERATOR_TYPE(FBulletAttributeDragDropOperation, FDragDropOperation)
	
	virtual void OnDragged(const class FDragDropEvent& DragDropEvent) override;

	virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;

	static TSharedRef<FBulletAttributeDragDropOperation> New(FText AttributeName);

	FText GetAttributeName() const { return AttributeName; }

private:
	FText AttributeName;
};
