// Fill out your copyright notice in the Description page of Project Settings.
#include "BulletEditorViewport.h"
#include "Danmaku/Editor/BulletEditor/BulletEditor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "Engine/StreamableManager.h"
#include "Materials/MaterialExpressionConstant3Vector.h"

FBulletEditorViewport::FBulletEditorViewport(FPreviewScene* InPreviewScene) : FEditorViewportClient(nullptr, InPreviewScene)
{
	PreviewScene = InPreviewScene;
	
	SetViewportType(ELevelViewportType::LVT_OrthoYZ);
	SetOrthoZoom(100000.0f);
	SetViewMode(VMI_Lit);

	auto CreateDanmakuActor = [=](FVector InLocation, FVector InScale, UStaticMesh* InStaticMesh, UMaterial* InMaterial) {
		FActorSpawnParameters ActorSpawnParamters = FActorSpawnParameters();
		ActorSpawnParamters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//���� ��Ʈ ������Ʈ�� ���� ������ ���忡 ��ǥ�� �������� ����.
		AActor* Actor = PreviewScene->GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), FVector::ZeroVector, FRotator(), ActorSpawnParamters);

		UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(Actor, UStaticMeshComponent::StaticClass(), FName("StaticMesh"));
		if (StaticMeshComponent)
		{
			StaticMeshComponent->RegisterComponent();
			StaticMeshComponent->SetRelativeLocation(InLocation);
			StaticMeshComponent->SetStaticMesh(InStaticMesh);
			StaticMeshComponent->SetRelativeScale3D(InScale);

			UMaterial* Material = InMaterial;
			if (IsValid(Material) == false)
			{
				Material = NewObject<UMaterial>(Actor, UMaterial::StaticClass(), FName("Material"));

				UMaterialExpressionConstant3Vector* BaseColorFactorNode = NewObject<UMaterialExpressionConstant3Vector>();
				BaseColorFactorNode->Constant = FColor::Red; 
				Material->BaseColor.Connect(0, BaseColorFactorNode);
				Material->PostEditChange();
			}
			StaticMeshComponent->SetMaterial(0, Material);

			Actor->SetRootComponent(StaticMeshComponent);
		}
	};

	FSoftObjectPath SphereObjectPath = TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'");
	TSoftObjectPtr<UStaticMesh> SphereObject(SphereObjectPath);

	//�� ����
	FSoftObjectPath RedMaterialPath = TEXT("Material'/Engine/EditorMaterials/WidgetMaterial_X.WidgetMaterial_X'");
	TSoftObjectPtr<UMaterial> RedMaterialObject(RedMaterialPath);
	CreateDanmakuActor(FVector(0, 0, 3000), FVector(1.0f, 1.0f, 1.0f), SphereObject.Get(), RedMaterialObject.Get());

	//�÷��̾� ����
	FSoftObjectPath BlueMaterialPath = TEXT("Material'/Engine/EditorMaterials/WidgetMaterial_Z.WidgetMaterial_Z'");
	TSoftObjectPtr<UMaterial> BlueMaterialObject(BlueMaterialPath);
	CreateDanmakuActor(FVector(0, 0, -3000), FVector(1.0f, 1.0f, 1.0f), SphereObject.Get(), BlueMaterialObject.Get());

	//�� ����
	FSoftObjectPath CubeObjectPath = TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'");
	TSoftObjectPtr<UStaticMesh> CubeObject(CubeObjectPath);
	
	FSoftObjectPath WhiteMaterialPath = TEXT("Material'/Engine/EditorMaterials/WidgetMaterial.WidgetMaterial'");
	TSoftObjectPtr<UMaterial> WhiteMaterialObject(WhiteMaterialPath);

	//4���� : Ȳ�ݺ�
	float ScaleRate = 70.0f;
	float Distance = 3470.0f;
	CreateDanmakuActor(FVector(0.0f, 0.0f, 1.618f * Distance), FVector(1.0f, 1.0f * ScaleRate, 1.0f), CubeObject.Get(), WhiteMaterialObject.Get());
	CreateDanmakuActor(FVector(0.0f, 0.0f, -1.618f * Distance), FVector(1.0f, 1.0f * ScaleRate, 1.0f), CubeObject.Get(), WhiteMaterialObject.Get());
	CreateDanmakuActor(FVector(0.0f, 1.0f * Distance, 0.0f ), FVector(1.0f, 1.0f, 1.618f * ScaleRate), CubeObject.Get(), WhiteMaterialObject.Get());
	CreateDanmakuActor(FVector(0.0f,-1.0f * Distance, 0.0f), FVector(1.0f, 1.0f, 1.618f * ScaleRate), CubeObject.Get(), WhiteMaterialObject.Get());

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

					//���� ����
					FBulletEditor::SetDetailViewObject(ConsideredActor);
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
