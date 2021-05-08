// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletEdGraphSchema.h"
#include "BulletEdGraphSchemaAction.h"
void UBulletEdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FBulletEdGraphSchemaAction> NewAction(new FBulletEdGraphSchemaAction());
	ContextMenuBuilder.AddAction(NewAction);
}
