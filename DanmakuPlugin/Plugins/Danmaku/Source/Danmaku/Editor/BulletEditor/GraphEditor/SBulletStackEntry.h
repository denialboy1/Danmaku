// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Views/STableViewBase.h"
#include "BulletStackEntry.h"
/**
 * 
 */
using FBulletStackEntryPtr = TSharedPtr<FBulletStackEntry>;
using SBulletStackEntryListView = SListView<FBulletStackEntryPtr>;

class DANMAKU_API SBulletStackEntry : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBulletStackEntry) {}
	SLATE_ARGUMENT(TArray<FBulletStackEntryPtr>, MoveAttributeList)
	SLATE_ARGUMENT(TArray<FBulletStackEntryPtr>, SpecialAttributeList)
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);
public:
	TSharedPtr<SBulletStackEntryListView> GetMoveAttributeListView() {return MoveAttributeListView;}

	TSharedPtr<SBulletStackEntryListView> GetSpecialAttributeListView() { return SpecialAttributeListView; }

	void RemoveListViewItem(FGuid InGuid);
private:
	//ListView�� �����ϴ� �Լ�
	TSharedRef<SWidget> CreateListView();

	//ListView���� ���پ� �߰��ɋ����� ȣ��Ǵ� �Լ� : ���ε����� ����� ����
	TSharedRef<ITableRow> GenerateListRow(FBulletStackEntryPtr BulletStackEntry, const TSharedRef<STableViewBase>& OwnerTable);
private:
	TSharedPtr<SBulletStackEntryListView> MoveAttributeListView;

	TArray<FBulletStackEntryPtr> MoveAttributeList;

	TSharedPtr<SBulletStackEntryListView> SpecialAttributeListView;

	TArray<FBulletStackEntryPtr> SpecialAttributeList;

};
