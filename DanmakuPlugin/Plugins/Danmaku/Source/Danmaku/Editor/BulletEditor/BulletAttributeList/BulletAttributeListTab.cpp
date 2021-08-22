// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletAttributeListTab.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "BulletAttributeDragDropOperation.h"

void SBulletAttributeEntryWidget::Construct(const FArguments& Args)
{
	const FButtonStyle& ButtonStyle = FEditorStyle::GetWidgetStyle<FButtonStyle>("PlacementBrowser.Asset");

	NormalImage = &ButtonStyle.Normal;
	HoverImage = &ButtonStyle.Hovered;
	PressedImage = &ButtonStyle.Pressed;

	BulletAttribute = *Args._BulletAttributePtr.Get();

	this->ChildSlot
		[
			SNew(SBorder)
			.BorderImage(this, &SBulletAttributeEntryWidget::GetBorder)
		    .Cursor(EMouseCursor::GrabHand)
		    [
      			SNew(STextBlock)
		    	.Text(FText::FromName(BulletAttribute))
		    ]
		];
}

FReply SBulletAttributeEntryWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsPressed = true;
		
		return FReply::Handled().DetectDrag(SharedThis(this), MouseEvent.GetEffectingButton());
	}

	return FReply::Unhandled();
}

FReply SBulletAttributeEntryWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsPressed = false;
	}

	return FReply::Unhandled();
}

FReply SBulletAttributeEntryWidget::OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	bIsPressed = false;

	if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return FReply::Handled().BeginDragDrop(FBulletAttributeDragDropOperation::CreateDragDropOperation(BulletAttribute));
	}
	else
	{
		return FReply::Handled();
	}
}

const FSlateBrush* SBulletAttributeEntryWidget::GetBorder() const
{
	if (bIsPressed)
	{
		return PressedImage;
	}
	else if (IsHovered())
	{
		return HoverImage;
	}
	else
	{
		return NormalImage;
	}
}

void SBulletAttributeListTab::Construct(const FArguments& Args)
{
	BulletAttributePtrList = Args._BulletAttributePtrList;

	BulletMovementAttributePtrList = Args._BulletMovementAttributePtrList;

	this->ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				CreateListView(TEXT("Movement"), BulletMovementAttributePtrList, BulletMovementAttributePtrListView)
			]
			+ SVerticalBox::Slot()
			[
				CreateListView(TEXT("Attribute"), BulletAttributePtrList, BulletAttributePtrListView)
			]
		];
	
	if (BulletAttributePtrListView)
	{
		BulletAttributePtrListView->RequestListRefresh();
	}
	
	if (BulletMovementAttributePtrListView)
	{
		BulletMovementAttributePtrListView->RequestListRefresh();
	}
}

TSharedRef<SWidget> SBulletAttributeListTab::CreateListView(FName ListName, FBulletAttributePtrList& ListPtr, TSharedPtr<SBulletAttributePtrListView> ListViewPtr)
{
	return SAssignNew(ListViewPtr, SBulletAttributePtrListView)
		.OnGenerateRow(this, &SBulletAttributeListTab::CreateListViewRow)
		.ListItemsSource(&ListPtr)
		.ItemHeight(24)
		.Visibility(EVisibility::Visible)
		.HeaderRow(
			SNew(SHeaderRow)
			+ SHeaderRow::Column(ListName)
			.DefaultLabel(FText::FromName(ListName))
			.FillWidth(1.0f)
		);
}

TSharedRef<ITableRow> SBulletAttributeListTab::CreateListViewRow(FBulletAttributePtr InBulletAttributePtr, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<FBulletAttributePtr>, OwnerTable)
		[
			SNew(SBulletAttributeEntryWidget)
			.BulletAttributePtr(InBulletAttributePtr)
		];
}
