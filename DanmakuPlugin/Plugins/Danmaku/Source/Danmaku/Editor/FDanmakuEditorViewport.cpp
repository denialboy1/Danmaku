// Fill out your copyright notice in the Description page of Project Settings.


#include "FDanmakuEditorViewport.h"
#include "Danmaku/Actor/Bullet/Bullet.h"

#include "AssetEditorModeManager.h"

FDanmakuEditorViewport::FDanmakuEditorViewport(class ABullet* InCustomAsset, FPreviewScene& InPreviewScene) : FEditorViewportClient(nullptr, &InPreviewScene), CustomAsset(InCustomAsset)
{
	((FAssetEditorModeManager*)ModeTools)->SetPreviewScene(PreviewScene);
	SetRealtime(true);
	UClass* MyActorBP = nullptr;//LoadClass<AActor>(NULL, TEXT("Blueprint'/))
	if (IsValid(MyActorBP))
	{
		PreviewScene->GetWorld()->SpawnActor<AActor>(MyActorBP, FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	}
	SetViewLocation(FVector(0.f, 0.f, 100.0f));
}

void FDanmakuEditorViewport::Tick(float DeltaSeconds)
{
	//FEditorViewportClient::Tick(DeltaSeconds);
	//PreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
}

