// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "BulletEdGraphSchemaAction.generated.h"

USTRUCT()
struct DANMAKU_API FBulletEdGraphSchemaAction : public FEdGraphSchemaAction
{
	GENERATED_BODY()
public:
	
	FBulletEdGraphSchemaAction() : FEdGraphSchemaAction(
		FText::FromString("Create"),
		FText::FromString("Movement"),
		FText::FromString("Movement Case"),
		0)
	{};

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
};
