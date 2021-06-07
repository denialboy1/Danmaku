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

	//지금은 임시로 속성 이름만 넘김, 추후에 데이터를 넘길 예정.
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
	// 새로 만든 아이템은 공유 포인터로 만들어야함!, 그래서 전역 함수로 이 아이템을 생성할수 있게 구현
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
	//ListView를 생성하는 함수
	TSharedRef<SWidget> CreateListView();

	//ListView에서 한줄씩 추가될떄마다 호출되는 함수 : 바인딩으로 사용할 예정
	TSharedRef<ITableRow> GenerateListRow(FBulletAttributeInfoPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable);
	
private:
	//SAssignNew때 보관할 리스트 변수
	TSharedPtr<SMovemnetListView> ListView;

	// ListView에 전달될 데이터 목록
	TArray<FBulletAttributeInfoPtr> BulletAttributeList;
};
