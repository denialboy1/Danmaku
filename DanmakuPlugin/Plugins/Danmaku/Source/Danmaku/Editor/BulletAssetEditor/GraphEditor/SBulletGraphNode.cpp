// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletGraphNode.h"
#include "BulletEdGraphNode.h"
#include "Danmaku/Editor/BulletAssetEditor/BulletAttributeList/BulletAttributeDragDropOperation.h"

#include "Widgets/Input/SButton.h"
#include "SNodePanel.h"

void SBulletGraphNode::Construct(const FArguments& InArgs, UBulletEdGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

FReply SBulletGraphNode::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	//드랍된 정보를 가져옴
	TSharedPtr<FBulletAttributeDragDropOperation> GraphDropOp = DragDropEvent.GetOperationAs<FBulletAttributeDragDropOperation>();
	
	if (GraphDropOp.IsValid() )
	{
		AddBulletAttribute(GraphDropOp->GetAttributeName());
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

TSharedRef<SWidget> SBulletGraphNode::CreateNodeContentArea()
{
	UBulletEdGraphNode* BulletEdGraphNode = Cast<UBulletEdGraphNode>(GraphNode);

	//원본 데이터를 StackNodeEntry 형태로 변경
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

void SBulletGraphNode::AddBulletAttribute(FText AttributeName)
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

