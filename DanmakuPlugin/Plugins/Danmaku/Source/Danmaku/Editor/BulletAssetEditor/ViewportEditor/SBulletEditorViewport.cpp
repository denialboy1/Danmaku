// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletEditorViewport.h"
#include "FBulletEditorViewport.h"

void SBulletEditorViewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

TSharedRef<FEditorViewportClient> SBulletEditorViewport::MakeEditorViewportClient()
{
	PreviewScene = MakeShareable(new FPreviewScene);

	TSharedPtr<FBulletEditorViewport> EditorViewportClient = MakeShareable(new FBulletEditorViewport(PreviewScene.Get()));

	return EditorViewportClient.ToSharedRef();
}
