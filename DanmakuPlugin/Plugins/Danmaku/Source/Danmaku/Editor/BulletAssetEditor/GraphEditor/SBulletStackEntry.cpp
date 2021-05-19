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

void SBulletStackEntry::AddBulletAttribute(FText AttributeName)
{
	FBulletStackEntryPtr BulletAttribute = FBulletStackEntry::Make();
	BulletAttribute->BulletAttribute = AttributeName.ToString();
	BulletStackEntryList.Add(BulletAttribute);

	this->ListView->RequestListRefresh();
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
			.Text(FText::FromString(BulletStackEntry->BulletAttribute))
		];
}

