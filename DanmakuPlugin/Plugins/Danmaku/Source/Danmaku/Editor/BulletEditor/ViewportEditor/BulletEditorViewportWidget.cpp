// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletEditorViewportWidget.h"
#include "BulletEditorViewport.h"

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

void SBulletEditorViewport::SetOrthoZoom(float InCameraDistance)
{
	if (EditorViewportClient)
	{
		EditorViewportClient->SetOrthoZoom(InCameraDistance);
	}
}

void SBulletEditorViewport::UpdateWallSize()
{
	if (EditorViewportClient)
	{
		EditorViewportClient->UpdateWallSize();
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

void SBulletEditorViewport::OnFocusViewportToSelection()
{
	UE_LOG(LogTemp, Log, TEXT("Selected"));
}

FReply SBulletEditorViewport::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	
	return SEditorViewport::OnFocusReceived(MyGeometry, InFocusEvent);
}

