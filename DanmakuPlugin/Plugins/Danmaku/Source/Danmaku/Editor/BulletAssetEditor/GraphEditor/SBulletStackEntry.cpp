// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletStackEntry.h"

void SBulletStackEntry::Construct(const FArguments& Args)
{
	this->ChildSlot
		[
			CreateListView()
		];

	this->ListView->RequestListRefresh();

	FBulletStackEntryPtr Attribute1 = FBulletStackEntry::Make();
	Attribute1->BulletAttribute = TEXT("Direction");
	FBulletStackEntryPtr Attribute2 = FBulletStackEntry::Make();;
	Attribute2->BulletAttribute = TEXT("Rotation");

	BulletAttributeList.Add(Attribute1);
	BulletAttributeList.Add(Attribute2);
}

TSharedRef<SWidget> SBulletStackEntry::CreateListView()
{
	return SAssignNew(this->ListView, SBulletStackEntryListView)
		.OnGenerateRow(this, &SBulletStackEntry::GenerateListRow)
		.ListItemsSource(&this->BulletAttributeList)
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
