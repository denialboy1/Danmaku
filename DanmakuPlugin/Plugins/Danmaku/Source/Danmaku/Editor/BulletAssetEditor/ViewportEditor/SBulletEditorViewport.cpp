// Fill out your copyright notice in the Description page of Project Settings.


#include "SBulletEditorViewport.h"
#include "FBulletEditorViewport.h"

void SBulletEditorViewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

void SBulletEditorViewport::PlaySimulation()
{
	if (EditorViewportClient)
	{
		EditorViewportClient->Play();
	}
	
}

void SBulletEditorViewport::StopSimulation()
{
	if (EditorViewportClient)
	{
		EditorViewportClient->Stop();
	}
	
}

void SBulletEditorViewport::PauseSimulation()
{
	if (EditorViewportClient)
	{
		EditorViewportClient->Pause();
	}
}

TSharedRef<FEditorViewportClient> SBulletEditorViewport::MakeEditorViewportClient()
{
	PreviewScene = MakeShareable(new FPreviewScene);

	if (PreviewScene)
	{
		EditorViewportClient = MakeShareable(new FBulletEditorViewport(PreviewScene.Get()));
		if (EditorViewportClient)
		{
			EditorViewportClient->SetRealtime(true);
		}
	}

	return EditorViewportClient.ToSharedRef();
}
