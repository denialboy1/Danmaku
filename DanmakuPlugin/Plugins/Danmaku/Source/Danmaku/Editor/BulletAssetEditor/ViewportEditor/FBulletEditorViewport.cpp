// Fill out your copyright notice in the Description page of Project Settings.
#include "FBulletEditorViewport.h"
#include "Danmaku/Editor/BulletAssetEditor/BulletAssetEditor.h"

#include "UObject/ConstructorHelpers.h"
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

void FBulletEditorViewport::ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY)
{
	FEditorViewportClient::ProcessClick(View, HitProxy, Key, Event, HitX, HitY);

	const FViewportClick Click(&View, this, Key, Event, HitX, HitY);
	if (Click.GetKey() == EKeys::LeftMouseButton)
	{
		if (HitProxy != nullptr)
		{
			if (HitProxy->IsA(HActor::StaticGetType()))
			{
				HActor* ActorHitProxy = (HActor*)HitProxy;
				AActor* ConsideredActor = ActorHitProxy->Actor;
				if (ConsideredActor) // It is possible to be clicking something during level transition if you spam click, and it might not be valid by this point
				{
					while (ConsideredActor->IsChildActor())
					{
						ConsideredActor = ConsideredActor->GetParentActor();
					}

					//액터 선택
					TSharedPtr<FBulletAssetEditor> BulletAssetEditor = FBulletAssetEditor::BulletAssetEditor;
					if (BulletAssetEditor)
					{
						TSharedPtr<IDetailsView> DetailView = FBulletAssetEditor::BulletAssetEditor->GetDetailView();
						if (DetailView)
						{
							DetailView->SetObject(ConsideredActor);
						}
					}
				}
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
