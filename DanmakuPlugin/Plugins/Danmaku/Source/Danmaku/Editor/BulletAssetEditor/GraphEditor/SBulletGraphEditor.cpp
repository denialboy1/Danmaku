// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletGraphEditor.h"
#include "Danmaku/Editor/BulletAssetEditor/GraphEditor/BulletEdGraph.h"
#include "Danmaku/Editor/BulletAssetEditor/GraphEditor/BulletEdGraphSchema.h"

void SBulletGraphEditor::Construct(const FArguments& Args)
{
	//Graph 积己
	GraphObj = NewObject<UBulletEdGraph>();

	//Graph 痹蘑 积己
	GraphObj->Schema = UBulletEdGraphSchema::StaticClass();
	GraphObj->AddToRoot();

	GraphObj->RebuildGraph();

	//Graph 俊叼磐 积己.
	GraphEditorPtr = SNew(SGraphEditor)
		.GraphToEdit(GraphObj);

	
	ChildSlot
		[
			GraphEditorPtr.ToSharedRef()
		];
}

