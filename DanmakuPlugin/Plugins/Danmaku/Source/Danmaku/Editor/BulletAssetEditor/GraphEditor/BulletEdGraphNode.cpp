// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletEdGraphNode.h"

void UBulletEdGraphNode::AddBulletAttribute(FText AttributeName)
{
	BulletAttributeList.Add(AttributeName);
}
