// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletEdGraph.h"
#include "BulletEdGraphNode.h"
#include "Danmaku/Editor/BulletAssetEditor/GraphEditor/BulletEdGraphNode.h"

void UBulletEdGraph::RebuildGraph()
{
	CreateNode(UBulletEdGraphNode::StaticClass());
}

UBulletEdGraphNode* UBulletEdGraph::CreateMovementNode()
{
	FGraphNodeCreator<UBulletEdGraphNode> NodeCreator(*this);
	UBulletEdGraphNode* Result = NodeCreator.CreateNode();
	NodeCreator.Finalize();
	return Result;
}
