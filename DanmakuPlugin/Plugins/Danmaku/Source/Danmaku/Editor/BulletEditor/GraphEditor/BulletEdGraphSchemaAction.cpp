// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletEdGraphSchemaAction.h"
#include "BulletEdGraph.h"
#include "BulletEdGraphNode.h"



UEdGraphNode* FBulletEdGraphSchemaAction::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	UBulletEdGraph* Graph = Cast<UBulletEdGraph>(ParentGraph);

	UBulletEdGraphNode* GraphNode = Graph->CreateBulletAttributeNode();
	GraphNode->NodePosX = Location.X;
	GraphNode->NodePosY = Location.Y;
	return nullptr;
}
