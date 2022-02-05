// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletStackEntry.h"

void SBulletStackEntry::Construct(const FArguments& Args)
{
	BulletStackEntryList = Args._BulletAttributeList;
	this->ChildSlot
		[
			CreateListView()
		];

	this->ListView->RequestListRefresh();
}

void SBulletStackEntry::RemoveListViewItem(FGuid InGuid)
{
	for (int32 Index = 0; Index < BulletStackEntryList.Num(); Index++)
	{
		if (BulletStackEntryList[Index]->Guid == InGuid)
		{
			BulletStackEntryList.RemoveAt(Index);
			break;
		}
	}

	ListView->RequestListRefresh();
}

TSharedRef<SWidget> SBulletStackEntry::CreateListView()
{
	return SAssignNew(this->ListView, SBulletStackEntryListView)
		.OnGenerateRow(this, &SBulletStackEntry::GenerateListRow)
		.ListItemsSource(&this->BulletStackEntryList)
		.ItemHeight(24)
		.Visibility(EVisibility::Visible);
}

TSharedRef<ITableRow> SBulletStackEntry::GenerateListRow(FBulletStackEntryPtr BulletStackEntry, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<FBulletStackEntryPtr>, OwnerTable)
		[
			SNew(STextBlock)
			.Text(FText::FromName(BulletStackEntry->AttributeName))
		];
}

