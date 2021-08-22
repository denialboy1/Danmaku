// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletGraphNode.h"
#include "BulletEdGraphNode.h"
#include "Danmaku/Editor/BulletEditor/BulletAttributeList/BulletAttributeDragDropOperation.h"
#include "Danmaku/Editor/BulletEditor/BulletEditor.h"

#include "Widgets/Input/SButton.h"
#include "SNodePanel.h"

void SBulletGraphNode::Construct(const FArguments& InArgs, UBulletEdGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

FReply SBulletGraphNode::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	//����� ������ ������
	TSharedPtr<FBulletAttributeDragDropOperation> GraphDropOp = DragDropEvent.GetOperationAs<FBulletAttributeDragDropOperation>();
	
	if (GraphDropOp.IsValid() )
	{
		AddBulletAttribute(GraphDropOp->GetAttributeName());
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply SBulletGraphNode::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FBulletEditor::SetDetailViewObject(GraphNode);

	return SGraphNode::OnMouseButtonDown(MyGeometry, MouseEvent);
}

TSharedRef<SWidget> SBulletGraphNode::CreateNodeContentArea()
{
	UBulletEdGraphNode* BulletEdGraphNode = Cast<UBulletEdGraphNode>(GraphNode);

	//���� �����͸� StackNodeEntry ���·� ����
	TArray<FBulletStackEntryPtr> BulletStackEntryList;
	for (auto BulletAttributeName : BulletEdGraphNode->GetBulletAttributeList())
	{
		FBulletStackEntryPtr BulletAttribute = FBulletStackEntry::Make();
		BulletAttribute->BulletAttribute = BulletAttributeName.ToString();
		BulletStackEntryList.Add(BulletAttribute);
	}

	return SAssignNew(BulletStackEntry, SBulletStackEntry)
		.BulletAttributeList(BulletStackEntryList);
}

void SBulletGraphNode::AddBulletAttribute(FName AttributeName)
{
	UBulletEdGraphNode* BulletEdGraphNode = Cast<UBulletEdGraphNode>(GraphNode);
	if (IsValid(BulletEdGraphNode))
	{
		BulletEdGraphNode->AddBulletAttribute(AttributeName);
	}
	
	if (BulletStackEntry)
	{
		BulletStackEntry->AddBulletAttribute(AttributeName);
	}
	
}

