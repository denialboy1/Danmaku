// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "BulletStackEntry.h"
#include "BulletEdGraph.generated.h"

UCLASS()
class DANMAKU_API UBulletEdGraph : public UEdGraph
{
	GENERATED_BODY()
	
public:
	void RebuildGraph();

	class UBulletEdGraphNode* CreateBulletAttributeNode();
};
