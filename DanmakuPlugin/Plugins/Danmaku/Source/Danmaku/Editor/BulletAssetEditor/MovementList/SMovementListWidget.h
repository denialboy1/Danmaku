// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Views/STableViewBase.h"

#include "Styling/SlateBrush.h"


struct FMovementInfo
{
public:
	FString MovementName;

public:
	// 새로 만든 아이템은 공유 포인터로 만들어야함!, 그래서 전역 함수로 이 아이템을 생성할수 있게 구현
	static TSharedRef<FMovementInfo> Make(FString MovementName)
	{
		return MakeShareable(new FMovementInfo(MovementName));
	}

protected:

	// Hidden constructor, always use Make above
	FMovementInfo(FString MovementName)	:
		MovementName(MovementName)
	{}
	
	// Hidden constructor, always use Make above
	FMovementInfo() {}
};


using FMovementInfoPtr = TSharedPtr<FMovementInfo>;
using SMovemnetListView = SListView<FMovementInfoPtr>;

DECLARE_DELEGATE_OneParam(FOnRefreshListView, TArray<FMovementInfoPtr>&);

class DANMAKU_API SMovementListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMovementListWidget) : _DataList() {
		_DataList = TArray<FMovementInfoPtr>();
	}

	SLATE_ARGUMENT(TArray<FMovementInfoPtr>, DataList)

	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

private:
	//ListView를 생성하는 함수
	TSharedRef<SWidget> CreateListView();

	//ListView에서 한줄씩 추가될떄마다 호출되는 함수 : 바인딩으로 사용할 예정
	TSharedRef<ITableRow> GenerateListRow(FMovementInfoPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable);
	
private:
	//SAssignNew때 보관할 리스트 변수
	TSharedPtr<SMovemnetListView> ListView;

	// ListView에 전달될 데이터 목록
	TArray<FMovementInfoPtr> MovementList;
};
