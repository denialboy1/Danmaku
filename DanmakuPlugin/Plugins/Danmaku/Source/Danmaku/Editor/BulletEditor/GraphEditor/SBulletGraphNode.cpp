// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletGraphNode.h"
#include "BulletEdGraphNode.h"
#include "Danmaku/Editor/BulletEditor/BulletAttributeList/BulletAttributeDragDropOperation.h"
#include "Danmaku/Editor/BulletEditor/BulletEditor.h"

#include "Widgets/Input/SButton.h"
#include "SNodePanel.h"

void SBulletGraphNode::Construct(const FArguments& InArgs)
{
	GraphNode = InArgs._BulletEdGraphNode;
	UpdateGraphNode();
}

FReply SBulletGraphNode::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	//드랍된 정보를 가져옴
	TSharedPtr<FBulletAttributeDragDropOperation> GraphDropOp = DragDropEvent.GetOperationAs<FBulletAttributeDragDropOperation>();
	
	if (GraphDropOp.IsValid() )
	{
		if (GraphDropOp->GetBulletAttributeType() == EBulletAttributeType::Move)
		{
			AddBulletMoveAttribute(GraphDropOp->GetAttributeName());
		}
		else if(GraphDropOp->GetBulletAttributeType() == EBulletAttributeType::Special)
		{
			AddBulletSpecialAttribute(GraphDropOp->GetAttributeName());
		}
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply SBulletGraphNode::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FBulletEditor::SetDetailViewObject(GraphNode);

	return SGraphNode::OnMouseButtonDown(MyGeometry, MouseEvent);
}

FReply SBulletGraphNode::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Delete)
	{
		if (BulletStackEntry)
		{
			UBulletEdGraphNode* BulletGraphNode = Cast<UBulletEdGraphNode>(GraphNode);
			if (BulletGraphNode)
			{
				for (auto SelectedItem : BulletStackEntry->GetMoveAttributeListView()->GetSelectedItems())
				{
					//데이터 삭제
					BulletGraphNode->RemoveBulletAttribute(SelectedItem->Guid);

					//위젯 리스트 삭제
					BulletStackEntry->RemoveListViewItem(SelectedItem->Guid);
				}

				for (auto SelectedItem : BulletStackEntry->GetSpecialAttributeListView()->GetSelectedItems())
				{
					//데이터 삭제
					BulletGraphNode->RemoveBulletAttribute(SelectedItem->Guid);

					//위젯 리스트 삭제
					BulletStackEntry->RemoveListViewItem(SelectedItem->Guid);
				}
			}
		}

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

TSharedRef<SWidget> SBulletGraphNode::CreateNodeContentArea()
{
	UBulletEdGraphNode* BulletEdGraphNode = Cast<UBulletEdGraphNode>(GraphNode);

	//원본 데이터를 StackNodeEntry 형태로 변경
	TArray<FBulletStackEntryPtr> MoveAttributeList;
	for (auto BulletAttribute : BulletEdGraphNode->GetMoveAttributeList())
	{
		FBulletStackEntryPtr BulletStackEntryPtr = FBulletStackEntry::Make();
		BulletStackEntryPtr->AttributeName = BulletAttribute.AttributeName;
		BulletStackEntryPtr->Guid = BulletAttribute.Guid;

		MoveAttributeList.Add(BulletStackEntryPtr);
	}

	TArray<FBulletStackEntryPtr> SpecialAttributeList;
	for (auto BulletAttribute : BulletEdGraphNode->GetSpecialAttributeList())
	{
		FBulletStackEntryPtr BulletStackEntryPtr = FBulletStackEntry::Make();
		BulletStackEntryPtr->AttributeName = BulletAttribute.AttributeName;
		BulletStackEntryPtr->Guid = BulletAttribute.Guid;

		SpecialAttributeList.Add(BulletStackEntryPtr);
	}

	return SAssignNew(BulletStackEntry, SBulletStackEntry)
		.MoveAttributeList(MoveAttributeList)
		.SpecialAttributeList(SpecialAttributeList);
}

void SBulletGraphNode::AddBulletMoveAttribute(FName AttributeName)
{
	UBulletEdGraphNode* BulletEdGraphNode = Cast<UBulletEdGraphNode>(GraphNode);
	if (IsValid(BulletEdGraphNode))
	{
		BulletEdGraphNode->AddMoveBulletAttribute(AttributeName);
	}

	UpdateGraphNode();
}

void SBulletGraphNode::AddBulletSpecialAttribute(FName AttributeName)
{
	UBulletEdGraphNode* BulletEdGraphNode = Cast<UBulletEdGraphNode>(GraphNode);
	if (IsValid(BulletEdGraphNode))
	{
		BulletEdGraphNode->AddSpecialBulletAttribute(AttributeName);
	}

	UpdateGraphNode();
}


