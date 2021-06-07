// Fill out your copyright notice in the Description page of Project Settings.
#include "FBulletEditorViewport.h"
#include "UObject/ConstructorHelpers.h"
FBulletEditorViewport::FBulletEditorViewport(FPreviewScene* InPreviewScene) : FEditorViewportClient(nullptr, InPreviewScene)
{
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
