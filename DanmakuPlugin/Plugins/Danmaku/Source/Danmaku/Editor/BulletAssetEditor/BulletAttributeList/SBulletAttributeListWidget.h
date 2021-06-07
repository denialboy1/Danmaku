// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Danmaku/Editor/BulletAssetEditor/GraphEditor/SBulletGraphTab.h"

#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Views/STableViewBase.h"
#include "Styling/SlateBrush.h"

class DANMAKU_API SBulletAttributeEntry : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBulletAttributeEntry) {}

	//������ �ӽ÷� �Ӽ� �̸��� �ѱ�, ���Ŀ� �����͸� �ѱ� ����.
	SLATE_ARGUMENT(FText, AttributeName)

	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	bool IsPressed() const;
private:
	const FSlateBrush* GetBorder() const;

	bool bIsPressed;

	/** Brush resource that represents a button */
	const FSlateBrush* NormalImage;
	/** Brush resource that represents a button when it is hovered */
	const FSlateBrush* HoverImage;
	/** Brush resource that represents a button when it is pressed */
	const FSlateBrush* PressedImage;

	FText AttributeName;
};


struct FBulletAttributeInfo
{
public:
	FString BulletAttributeName;

public:
	// ���� ���� �������� ���� �����ͷ� ��������!, �׷��� ���� �Լ��� �� �������� �����Ҽ� �ְ� ����
	static TSharedRef<FBulletAttributeInfo> Make(FString BulletAttributeName)
	{
		return MakeShareable(new FBulletAttributeInfo(BulletAttributeName));
	}

protected:

	// Hidden constructor, always use Make above
	FBulletAttributeInfo(FString BulletAttributeName)	:
		BulletAttributeName(BulletAttributeName)
	{}
	
	// Hidden constructor, always use Make above
	FBulletAttributeInfo() {}
};


using FBulletAttributeInfoPtr = TSharedPtr<FBulletAttributeInfo>;
using SMovemnetListView = SListView<FBulletAttributeInfoPtr>;

DECLARE_DELEGATE_OneParam(FOnRefreshListView, TArray<FBulletAttributeInfoPtr>&);

class DANMAKU_API SBulletAttributeListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBulletAttributeListWidget) : _DataList() {
		_DataList = TArray<FBulletAttributeInfoPtr>();
	}

	SLATE_ARGUMENT(TArray<FBulletAttributeInfoPtr>, DataList)

	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

private:
	//ListView�� �����ϴ� �Լ�
	TSharedRef<SWidget> CreateListView();

	//ListView���� ���پ� �߰��ɋ����� ȣ��Ǵ� �Լ� : ���ε����� ����� ����
	TSharedRef<ITableRow> GenerateListRow(FBulletAttributeInfoPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable);
	
private:
	//SAssignNew�� ������ ����Ʈ ����
	TSharedPtr<SMovemnetListView> ListView;

	// ListView�� ���޵� ������ ���
	TArray<FBulletAttributeInfoPtr> BulletAttributeList;
};
