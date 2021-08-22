// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletEdGraphNode.h"

void UBulletEdGraphNode::AddBulletAttribute(FName AttributeName)
{
	BulletAttributeList.Add(AttributeName);
}
