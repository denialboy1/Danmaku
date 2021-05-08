// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "BulletEdGraphSchema.generated.h"

/**
 * 
 */
UCLASS()
class DANMAKU_API UBulletEdGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()
	
	void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const;
};
