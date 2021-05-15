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
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

private:
	//ListView를 생성하는 함수
	TSharedRef<SWidget> CreateListView();

	//ListView에서 한줄씩 추가될떄마다 호출되는 함수 : 바인딩으로 사용할 예정
	TSharedRef<ITableRow> GenerateListRow(FBulletStackEntryPtr BulletStackEntry, const TSharedRef<STableViewBase>& OwnerTable);

private:
	//SAssignNew때 보관할 리스트 변수
	TSharedPtr<SBulletStackEntryListView> ListView;

	// ListView에 전달될 데이터 목록
	TArray<FBulletStackEntryPtr> BulletAttributeList;
};
