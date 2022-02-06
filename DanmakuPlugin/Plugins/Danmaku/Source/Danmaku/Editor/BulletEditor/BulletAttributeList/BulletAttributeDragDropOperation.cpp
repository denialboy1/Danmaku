// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletAttributeDragDropOperation.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/SBulletGraphTab.h"

void FBulletAttributeDragDropOperation::OnDragged(const class FDragDropEvent& DragDropEvent)
{
	if (CursorDecoratorWindow.IsValid())
	{
		CursorDecoratorWindow->MoveWindowTo(DragDropEvent.GetScreenSpacePosition());
	}
}

TSharedPtr<SWidget> FBulletAttributeDragDropOperation::GetDefaultDecorator() const
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SSpacer)
			.Size(FVector2D(15.f, 0))
		]
	+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(STextBlock)
			.Text(FText::FromName(AttributeName))
		.Cursor(EMouseCursor::GrabHandClosed)
		];

}

TSharedRef<FBulletAttributeDragDropOperation> FBulletAttributeDragDropOperation::CreateDragDropOperation(FBulletAttributeInfo InBulletAttributeInfo)
{
	TSharedRef<FBulletAttributeDragDropOperation> Operation = MakeShareable(new FBulletAttributeDragDropOperation);

	Operation->AttributeName = InBulletAttributeInfo.AttributeName;
	Operation->BulletAttributeType = InBulletAttributeInfo.BulletAttributeType;
	Operation->Construct();

	return Operation;
}
