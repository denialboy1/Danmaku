// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletAttributeListWidget.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "BulletAttributeDragDropOperation.h"


#define LOCTEXT_NAMESPACE "BulletAttributeList"
void SBulletAttributeListWidget::Construct(const FArguments& Args)
{
	BulletAttributeList = Args._DataList;

	this->ChildSlot
		[
			CreateListView()
		];

	this->ListView->RequestListRefresh();
}

TSharedRef<SWidget> SBulletAttributeListWidget::CreateListView()
{
	return SAssignNew(this->ListView, SMovemnetListView)
		.OnGenerateRow(this, &SBulletAttributeListWidget::GenerateListRow)
		.ListItemsSource(&this->BulletAttributeList)
		.ItemHeight(24)
		.Visibility(EVisibility::Visible)
		.HeaderRow(
			SNew(SHeaderRow)
			+ SHeaderRow::Column("BulletAttribute")
			.DefaultLabel(LOCTEXT("BulletAttributeLabel", "BulletAttribute"))
			.FillWidth(1.0f)
		);
}

TSharedRef<ITableRow> SBulletAttributeListWidget::GenerateListRow(FBulletAttributeInfoPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<FBulletAttributeInfoPtr>, OwnerTable)
		[
			SNew(SBulletAttributeEntry)
				.AttributeName(FText::FromString(InInfo->BulletAttributeName))
		];
}

#undef LOCTEXT_NAMESPACE

void SBulletAttributeEntry::Construct(const FArguments& Args)
{
	const FButtonStyle& ButtonStyle = FEditorStyle::GetWidgetStyle<FButtonStyle>("PlacementBrowser.Asset");

	NormalImage = &ButtonStyle.Normal;
	HoverImage = &ButtonStyle.Hovered;
	PressedImage = &ButtonStyle.Pressed;

	AttributeName = Args._AttributeName;

	this->ChildSlot
		[
			SNew(SBorder)
			.BorderImage(this, &SBulletAttributeEntry::GetBorder)
		    .Cursor(EMouseCursor::GrabHand)
		    [
      			SNew(STextBlock)
		    	.Text(Args._AttributeName)
		    ]
		];
}

FReply SBulletAttributeEntry::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsPressed = true;
		
		return FReply::Handled().DetectDrag(SharedThis(this), MouseEvent.GetEffectingButton());
	}

	return FReply::Unhandled();
}

FReply SBulletAttributeEntry::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsPressed = false;
	}

	return FReply::Unhandled();
}

FReply SBulletAttributeEntry::OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	bIsPressed = false;

	if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return FReply::Handled().BeginDragDrop(FBulletAttributeDragDropOperation::New(AttributeName));
	}
	else
	{
		return FReply::Handled();
	}
}

bool SBulletAttributeEntry::IsPressed() const
{
	return bIsPressed;
}

const FSlateBrush* SBulletAttributeEntry::GetBorder() const
{
	if (IsPressed())
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
