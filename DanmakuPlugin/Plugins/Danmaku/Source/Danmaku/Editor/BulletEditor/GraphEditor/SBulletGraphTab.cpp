// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletGraphTab.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/BulletEdGraph.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/BulletEdGraphSchema.h"

void SBulletGraphTab::Construct(const FArguments& Args)
{
	//Graph 생성
	UBulletEdGraph* BulletEdGraph = NewObject<UBulletEdGraph>();
	if (IsValid(BulletEdGraph))
	{
		BulletEdGraph->SetBulletFactory(Args._BulletFactory);

		//Graph 규칙 생성
		BulletEdGraph->Schema = UBulletEdGraphSchema::StaticClass();
		BulletEdGraph->AddToRoot();


		//#todo 
		//BulletFactory에서 얻은 데이터를 통해
		//Node가 여러개이면 여러개 생성해줘야함.
		//지금은 임시로 하나만 생성하고 거기에 데이터 설정해줌.
		for (int32 Index = 0; Index < Args._BulletFactory->GetDataCount(); Index++)
		{
			UBulletEdGraphNode* BulletEdGraphNode = BulletEdGraph->CreateIntermediateNode<UBulletEdGraphNode>();
			if (IsValid(BulletEdGraphNode))
			{
				BulletEdGraphNode->SetNodeIndex(Index);

				for (auto BulletAttributeName : Args._BulletFactory->GetBulletAttributeList(Index).BulletAttributeList)
				{
					BulletEdGraphNode->AddBulletAttribute(BulletAttributeName);
				}
			}
		}
		

	}

	//Graph 에디터 생성.
	GraphEditorPtr = SNew(SGraphEditor)
		.GraphToEdit(BulletEdGraph);

	
	ChildSlot
		[
			GraphEditorPtr.ToSharedRef()
		];
}

