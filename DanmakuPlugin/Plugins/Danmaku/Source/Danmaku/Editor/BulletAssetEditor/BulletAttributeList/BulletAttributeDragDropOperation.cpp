// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletAttributeDragDropOperation.h"
#include "Danmaku/Editor/BulletAssetEditor/GraphEditor/SBulletGraphTab.h"

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
			.Text(AttributeName)
		.Cursor(EMouseCursor::GrabHandClosed)
		];

}

TSharedRef<FBulletAttributeDragDropOperation> FBulletAttributeDragDropOperation::New(FText AttributeName)// , TSharedPtr<SBulletGraphEditor> BulletGraphEditor)
{
	TSharedRef<FBulletAttributeDragDropOperation> Operation = MakeShareable(new FBulletAttributeDragDropOperation);

	Operation->AttributeName = AttributeName;
	Operation->Construct();

	return Operation;
}
