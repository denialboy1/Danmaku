// Fill out your copyright notice in the Description page of Project Settings.


#include "SMovementListWidget.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "ContentBrowserDataDragDropOp.h"
#define LOCTEXT_NAMESPACE "MovementList"


void SMovementListWidget::Construct(const FArguments& Args)
{
	MovementList = Args._DataList;

	this->ChildSlot
		[
			CreateListView()
		];

	this->ListView->RequestListRefresh();
}

TSharedRef<SWidget> SMovementListWidget::CreateListView()
{
	return SAssignNew(this->ListView, SMovemnetListView)
		.OnGenerateRow(this, &SMovementListWidget::GenerateListRow)
		.ListItemsSource(&this->MovementList)
		.ItemHeight(24)
		.Visibility(EVisibility::Visible)
		.HeaderRow(
			SNew(SHeaderRow)
			+ SHeaderRow::Column("Movement")
			.DefaultLabel(LOCTEXT("MovementLabel", "Movement"))
			.FillWidth(1.0f)
		);
}

TSharedRef<ITableRow> SMovementListWidget::GenerateListRow(FMovementInfoPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<FMovementInfoPtr>, OwnerTable)
		[
			SNew(STextBlock)
				.Text(FText::FromString(InInfo->MovementName))
		];
}

#undef LOCTEXT_NAMESPACE
