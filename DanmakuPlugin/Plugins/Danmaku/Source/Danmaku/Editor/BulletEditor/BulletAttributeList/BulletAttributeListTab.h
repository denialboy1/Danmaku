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
	//ListView�� �����ϴ� �Լ�
	TSharedRef<SWidget> CreateListView(FName ListName, FBulletAttributePtrList& ListPtr, TSharedPtr<SBulletAttributePtrListView> ListViewPtr);

	//ListView���� ���پ� �߰��ɋ����� ȣ��Ǵ� �Լ� : ���ε����� ����� ����
	TSharedRef<ITableRow> CreateListViewRow(FBulletAttributePtr InBulletAttributePtr, const TSharedRef<STableViewBase>& OwnerTable);
	
private:
	//SAssignNew�� ������ ����Ʈ ����
	TSharedPtr<SBulletAttributePtrListView> MoveAttributePtrListView;

	TSharedPtr<SBulletAttributePtrListView> SpecialAttributePtrListView;

	// ListView�� ���޵� ������ ���
	FBulletAttributePtrList MoveAttributePtrList;

	FBulletAttributePtrList SpecialAttributePtrList;
};
