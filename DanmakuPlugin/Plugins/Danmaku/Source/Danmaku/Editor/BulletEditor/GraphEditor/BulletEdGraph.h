// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "BulletStackEntry.h"
#include "Danmaku/Editor/BulletEditor/BulletFactory.h"
#include "BulletEdGraphNode.h"
#include "BulletEdGraph.generated.h"

class UBulletFactory;

UCLASS()
class DANMAKU_API UBulletEdGraph : public UEdGraph
{
	GENERATED_BODY()
public:
	class UBulletEdGraphNode* CreateBulletAttributeNode();
};
