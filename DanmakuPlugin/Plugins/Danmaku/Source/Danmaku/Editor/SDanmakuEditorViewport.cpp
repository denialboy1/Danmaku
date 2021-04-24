// Fill out your copyright notice in the Description page of Project Settings.


#include "SDanmakuEditorViewport.h"
#include "Kismet2/DebuggerCommands.h"
#include "PreviewScene.h"
#include "Widgets/Layout/SUniformGridPanel.h"


SDanmakuEditorViewport::SDanmakuEditorViewport()
{
}

SDanmakuEditorViewport::~SDanmakuEditorViewport()
{
}

void SDanmakuEditorViewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
}


TSharedRef<FEditorViewportClient> SDanmakuEditorViewport::MakeEditorViewportClient() 
{
	PreviewScene = MakeShareable(new FPreviewScene);

	TSharedPtr<FEditorViewportClient> EditorViewportClient = MakeShareable(new FEditorViewportClient(nullptr, PreviewScene.Get()));

	return EditorViewportClient.ToSharedRef();
}

