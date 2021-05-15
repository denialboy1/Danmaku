// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletGraphNode.h"
#include "Danmaku/Editor/BulletAssetEditor/GraphEditor/BulletEdGraphNode.h"

#include "Widgets/Input/SButton.h"
#include "SNodePanel.h"

void SBulletGraphNode::Construct(const FArguments& InArgs, class UBulletEdGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

TSharedRef<SWidget> SBulletGraphNode::CreateNodeContentArea()
{
	return SAssignNew(BulletStackEntry,SBulletStackEntry);
}

//void SBulletGraphNode::UpdateGraphNode()
//{
//	GetOrAddSlot(ENodeZone::Center)
//	[
//		SNew(SButton).Text(FText::FromString("Hello"))
//	];
//}
