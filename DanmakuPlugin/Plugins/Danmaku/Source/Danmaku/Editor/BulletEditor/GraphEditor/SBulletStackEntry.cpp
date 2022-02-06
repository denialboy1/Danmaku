// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletStackEntry.h"

void SBulletStackEntry::Construct(const FArguments& Args)
{
	MoveAttributeList = Args._MoveAttributeList;
	SpecialAttributeList = Args._SpecialAttributeList;
	this->ChildSlot
		[
			CreateListView()
		];

	MoveAttributeListView->RequestListRefresh();
	SpecialAttributeListView->RequestListRefresh();
}

void SBulletStackEntry::RemoveListViewItem(FGuid InGuid)
{
	for (int32 Index = 0; Index < MoveAttributeList.Num(); Index++)
	{
		if (MoveAttributeList[Index]->Guid == InGuid)
		{
			MoveAttributeList.RemoveAt(Index);

			MoveAttributeListView->RequestListRefresh();
			return;
		}
	}

	for (int32 Index = 0; Index < SpecialAttributeList.Num(); Index++)
	{
		if (SpecialAttributeList[Index]->Guid == InGuid)
		{
			SpecialAttributeList.RemoveAt(Index);
			
			SpecialAttributeListView->RequestListRefresh();
			return;
		}
	}

	
}

TSharedRef<SWidget> SBulletStackEntry::CreateListView()
{
	return SNew(SVerticalBox)
		
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(this->MoveAttributeListView, SBulletStackEntryListView)
			.OnGenerateRow(this, &SBulletStackEntry::GenerateListRow)
		.ListItemsSource(&this->MoveAttributeList)
		.ItemHeight(24)
		.Visibility(EVisibility::Visible)
		.HeaderRow(
			SNew(SHeaderRow)
			+ SHeaderRow::Column("MovementAttribute")
		)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(this->SpecialAttributeListView, SBulletStackEntryListView)
			.OnGenerateRow(this, &SBulletStackEntry::GenerateListRow)
		.ListItemsSource(&this->SpecialAttributeList)
		.ItemHeight(24)
		.Visibility(EVisibility::Visible)
		.HeaderRow(
			SNew(SHeaderRow)
			+ SHeaderRow::Column("SpecialAttribute")
		)
		];
		
}

TSharedRef<ITableRow> SBulletStackEntry::GenerateListRow(FBulletStackEntryPtr BulletStackEntry, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<FBulletStackEntryPtr>, OwnerTable)
		[
			SNew(STextBlock)
			.Text(FText::FromName(BulletStackEntry->AttributeName))
			.Margin(10.0f)
			.AutoWrapText(true)
		];
}

