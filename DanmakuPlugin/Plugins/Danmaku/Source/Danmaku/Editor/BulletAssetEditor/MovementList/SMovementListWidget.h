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
	// ���� ���� �������� ���� �����ͷ� ��������!, �׷��� ���� �Լ��� �� �������� �����Ҽ� �ְ� ����
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
	//ListView�� �����ϴ� �Լ�
	TSharedRef<SWidget> CreateListView();

	//ListView���� ���پ� �߰��ɋ����� ȣ��Ǵ� �Լ� : ���ε����� ����� ����
	TSharedRef<ITableRow> GenerateListRow(FMovementInfoPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable);
	
private:
	//SAssignNew�� ������ ����Ʈ ����
	TSharedPtr<SMovemnetListView> ListView;

	// ListView�� ���޵� ������ ���
	TArray<FMovementInfoPtr> MovementList;
};
