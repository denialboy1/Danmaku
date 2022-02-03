// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletEdGraphNode.h"
#include "BulletEdGraph.h"


void UBulletEdGraphNode::AddBulletAttribute(FName AttributeName)
{
	UBulletEdGraph* BulletEdGraph = Cast<UBulletEdGraph>(GetGraph());

	if (IsValid(BulletEdGraph))
	{
		BulletEdGraph->SaveTempAttribute(NodeIndex, AttributeName);

		BulletAttributeList.Add(AttributeName);
	}
}
