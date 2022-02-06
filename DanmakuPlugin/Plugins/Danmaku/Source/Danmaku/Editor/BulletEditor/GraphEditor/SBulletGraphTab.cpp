// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletGraphTab.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/BulletEdGraph.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/BulletEdGraphSchema.h"

void SBulletGraphTab::Construct(const FArguments& Args)
{
	//Graph 积己
	BulletEdGraph = NewObject<UBulletEdGraph>();
	if (IsValid(BulletEdGraph))
	{
		//Graph 痹蘑 积己
		BulletEdGraph->Schema = UBulletEdGraphSchema::StaticClass();
		BulletEdGraph->AddToRoot();

		for (int32 Index = 0; Index < Args._BulletDataArray.Num(); Index++)
		{
			UBulletEdGraphNode* BulletEdGraphNode = BulletEdGraph->CreateIntermediateNode<UBulletEdGraphNode>();
			if (IsValid(BulletEdGraphNode))
			{
				BulletEdGraphNode->SetNodeIndex(Index);

				for (auto BulletAttributeName : Args._BulletDataArray[Index].MoveAttributeList)
				{
					BulletEdGraphNode->AddMoveBulletAttribute(BulletAttributeName);
				}

				for (auto BulletAttributeName : Args._BulletDataArray[Index].SpecialAttributeList)
				{
					BulletEdGraphNode->AddSpecialBulletAttribute(BulletAttributeName);
				}
			}
		}
	}

	//Graph 俊叼磐 积己.
	GraphEditorPtr = SNew(SGraphEditor)
		.GraphToEdit(BulletEdGraph);

	
	ChildSlot
		[
			GraphEditorPtr.ToSharedRef()
		];
}

