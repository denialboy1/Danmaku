// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletGraphEditor.h"
#include "Danmaku/Editor/BulletAssetEditor/GraphEditor/BulletEdGraph.h"
#include "Danmaku/Editor/BulletAssetEditor/GraphEditor/BulletEdGraphSchema.h"

void SBulletGraphEditor::Construct(const FArguments& Args)
{
	//Graph ����
	GraphObj = NewObject<UBulletEdGraph>();

	//Graph ��Ģ ����
	GraphObj->Schema = UBulletEdGraphSchema::StaticClass();
	GraphObj->AddToRoot();

	GraphObj->RebuildGraph();

	//Graph ������ ����.
	GraphEditorPtr = SNew(SGraphEditor)
		.GraphToEdit(GraphObj);

	
	ChildSlot
		[
			GraphEditorPtr.ToSharedRef()
		];
}

