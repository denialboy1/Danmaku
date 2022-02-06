// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Danmaku/Editor/BulletEditor/GraphEditor/SBulletGraphTab.h"
#include "Danmaku/Editor/BulletEditor/BulletEditorDefine.h"

#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Views/STableViewBase.h"
#include "Styling/SlateBrush.h"

using FBulletAttributePtr = TSharedPtr<FBulletAttributeInfo>;
using FBulletAttributePtrList = TArray<FBulletAttributePtr>;
using SBulletAttributePtrListView = SListView<FBulletAttributePtr>;

DECLARE_DELEGATE_OneParam(FOnRefreshListView, FBulletAttributePtrList&);

class DANMAKU_API SBulletAttributeEntryWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBulletAttributeEntryWidget) {}

	SLATE_ARGUMENT(FBulletAttributePtr, BulletAttributePtr)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& Args);

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

private:
	const FSlateBrush* GetBorder() const;

private:

	bool bIsPressed;

	/** Brush resource that represents a button */
	const FSlateBrush* NormalImage;
	/** Brush resource that represents a button when it is hovered */
	const FSlateBrush* HoverImage;
	/** Brush resource that represents a button when it is pressed */
	const FSlateBrush* PressedImage;

	FBulletAttributeInfo BulletAttributeInfo;
};

class DANMAKU_API SBulletAttributeListTab : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBulletAttributeListTab) {}

	SLATE_ARGUMENT(FBulletAttributePtrList, MoveAttributePtrList)

	SLATE_ARGUMENT(FBulletAttributePtrList, SpecialAttributePtrList)

	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

private:
	//ListView를 생성하는 함수
	TSharedRef<SWidget> CreateListView(FName ListName, FBulletAttributePtrList& ListPtr, TSharedPtr<SBulletAttributePtrListView> ListViewPtr);

	//ListView에서 한줄씩 추가될떄마다 호출되는 함수 : 바인딩으로 사용할 예정
	TSharedRef<ITableRow> CreateListViewRow(FBulletAttributePtr InBulletAttributePtr, const TSharedRef<STableViewBase>& OwnerTable);
	
private:
	//SAssignNew때 보관할 리스트 변수
	TSharedPtr<SBulletAttributePtrListView> MoveAttributePtrListView;

	TSharedPtr<SBulletAttributePtrListView> SpecialAttributePtrListView;

	// ListView에 전달될 데이터 목록
	FBulletAttributePtrList MoveAttributePtrList;

	FBulletAttributePtrList SpecialAttributePtrList;
};
