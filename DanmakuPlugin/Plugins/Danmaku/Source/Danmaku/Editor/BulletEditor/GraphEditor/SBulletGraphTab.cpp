// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletGraphTab.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/BulletEdGraph.h"
#include "Danmaku/Editor/BulletEditor/GraphEditor/BulletEdGraphSchema.h"

void SBulletGraphTab::Construct(const FArguments& Args)
{
	//Graph ����
	UBulletEdGraph* BulletEdGraph = NewObject<UBulletEdGraph>();
	if (IsValid(BulletEdGraph))
	{
		BulletEdGraph->SetBulletFactory(Args._BulletFactory);

		//Graph ��Ģ ����
		BulletEdGraph->Schema = UBulletEdGraphSchema::StaticClass();
		BulletEdGraph->AddToRoot();


		//#todo 
		//BulletFactory���� ���� �����͸� ����
		//Node�� �������̸� ������ �����������.
		//������ �ӽ÷� �ϳ��� �����ϰ� �ű⿡ ������ ��������.
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

	//Graph ������ ����.
	GraphEditorPtr = SNew(SGraphEditor)
		.GraphToEdit(BulletEdGraph);

	
	ChildSlot
		[
			GraphEditorPtr.ToSharedRef()
		];
}

