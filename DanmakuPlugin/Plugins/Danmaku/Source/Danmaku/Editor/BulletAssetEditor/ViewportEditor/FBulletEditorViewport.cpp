// Fill out your copyright notice in the Description page of Project Settings.
#include "FBulletEditorViewport.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"
#include "EngineUtils.h"

FBulletEditorViewport::FBulletEditorViewport(FPreviewScene* InPreviewScene) : FEditorViewportClient(nullptr, InPreviewScene)
{
	PreviewScene = InPreviewScene;

	auto CreateEditorActor = [=](AActor* Actor, FString BPPath, FVector Location, FRotator Rotation)
	{
		UClass* BPClass = LoadClass<AActor>(NULL, *BPPath);
		if (IsValid(BPClass))
		{
			Actor = PreviewScene->GetWorld()->SpawnActor<AActor>(BPClass, Location, Rotation);
			
		}
		else
		{
			Actor = PreviewScene->GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), Location, Rotation);
		}
		Actor->SetActorScale3D(FVector(0.1f, 0.1f, 0.1f));
	};

	CreateEditorActor(Enemy, TEXT("Blueprint'/Danmaku/Actor/Enemy/BulletEditorEnemy/BulletEditorEnemy.BulletEditorEnemy_C'"), FVector(0,0, 500.f), FRotator(0,0,0));
	CreateEditorActor(Bullet, TEXT("Blueprint'/Danmaku/Actor/Bullet/Bullet/BulletEditorBullet.BulletEditorBullet_C'"), FVector(0, 0, -500.f), FRotator(0, 0, 0));

	SetViewLocation(FVector(0.0f, 0.0f, 100000.0f));
	SetViewportType(ELevelViewportType::LVT_OrthoYZ);
	SetViewMode(VMI_Lit);

	
}

void FBulletEditorViewport::Tick(float DeltaTime)
{
	FEditorViewportClient::Tick(DeltaTime);

	if (BulletEditorPlayType == EBulletEditorPlayType::PLAY)
	{
		UWorld* PreviewWorld = PreviewScene->GetWorld();
		for (TActorIterator<AActor> It(PreviewWorld); It; ++It)
		{
			AActor* Actor = *It;
			if (!Actor->IsPendingKillPending())
			{
				Actor->SetActorLocation(Actor->GetActorLocation() + FVector(0, 2.0f * DeltaTime, 0));
			}
		}
	}
}

void FBulletEditorViewport::Play()
{
	if (BulletEditorPlayType == EBulletEditorPlayType::STOP)
	{
		SaveInitData();
	}

	BulletEditorPlayType = EBulletEditorPlayType::PLAY;
}

void FBulletEditorViewport::Stop()
{
	BulletEditorPlayType = EBulletEditorPlayType::STOP;

	UWorld* PreviewWorld = PreviewScene->GetWorld();
	for (TActorIterator<AActor> It(PreviewWorld); It; ++It)
	{
		AActor* Actor = *It;
		if (!Actor->IsPendingKillPending())
		{
			FString ActorName;
			Actor->GetName(ActorName);

			if (InitDataList.Contains(ActorName))
			{
				Actor->SetActorLocation(InitDataList[ActorName]);
			}
		}
	}
}

void FBulletEditorViewport::Pause()
{
	BulletEditorPlayType = EBulletEditorPlayType::PAUSE;
}

void FBulletEditorViewport::SaveInitData()
{
	InitDataList.Empty();

	UWorld* PreviewWorld = PreviewScene->GetWorld();
	for (TActorIterator<AActor> It(PreviewWorld); It; ++It)
	{
		AActor* Actor = *It;
		if (!Actor->IsPendingKillPending())
		{
			FString ActorName;
			Actor->GetName(ActorName);
			InitDataList.Add(ActorName, Actor->GetActorLocation());
		}
	}
}
