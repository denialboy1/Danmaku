// Fill out your copyright notice in the Description page of Project Settings.
#include "BulletEditorViewport.h"
#include "Danmaku/Editor/BulletEditor/BulletEditor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "Engine/StreamableManager.h"
#include "Materials/MaterialExpressionConstant3Vector.h"
#include "Engine/AssetManager.h"
#include "Danmaku/Movement/BulletMovementComponent.h"
#include "Danmaku/Actor/DanmakuBullet/DanmakuBullet.h"
#include "Danmaku/Editor/BulletEditor/BulletEditorSetting.h"
#include "Danmaku/Actor/DanmakuActor/DanmakuActor.h"
#include "Engine/EngineTypes.h"
#include "Danmaku/Editor/BulletEditor/BulletEditorDetailCustomization.h"
FBulletEditorViewport::FBulletEditorViewport(FPreviewScene* InPreviewScene) : FEditorViewportClient(nullptr, InPreviewScene)
{
	PreviewScene = InPreviewScene;
	
	SetViewportType(ELevelViewportType::LVT_OrthoXY);

	FBulletEditor::GetBulletEditorSettingInstance()->SetCameraDistance(100000.0f);
	SetOrthoZoom(FBulletEditor::GetBulletEditorSettingInstance()->GetCameraDistance());

	SetViewMode(VMI_Lit);

	SetIsSimulateInEditorViewport(true);
	
	auto CreateDanmakuActor = [this](FVector InLocation, UMaterial* InMaterial, FString InTagName) -> ADanmakuActor*
	{
		FSoftObjectPath SphereObjectPath = TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'");
		TSoftObjectPtr<UStaticMesh> SphereObject(SphereObjectPath);

		if (PreviewScene && PreviewScene->GetWorld())
		{
			FActorSpawnParameters ActorSpawnParamters = FActorSpawnParameters();
			ActorSpawnParamters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			ADanmakuActor* DanmakuActor = PreviewScene->GetWorld()->SpawnActor<ADanmakuActor>(ADanmakuActor::StaticClass(), InLocation, FRotator(), ActorSpawnParamters);

			if (DanmakuActor)
			{
				UStaticMeshComponent* StaticMeshComponent = DanmakuActor->FindComponentByClass<UStaticMeshComponent>();

				StaticMeshComponent->SetStaticMesh(SphereObject.Get());
				StaticMeshComponent->SetMaterial(0, InMaterial);

				DanmakuActor->Tags.Add(*InTagName);

				return DanmakuActor;
			}
		}

		return nullptr;
	};

	//Player 생성
	FSoftObjectPath PlayerMaterialPath = TEXT("Material'/Engine/EditorMaterials/WidgetMaterial_Z.WidgetMaterial_Z'");
	TSoftObjectPtr<UMaterial> PlayerMaterialObject(PlayerMaterialPath);
	Player = CreateDanmakuActor(FVector(0, 4000, 0), PlayerMaterialObject.Get(), TEXT("Player"));
	if (IsValid(Player))
	{
		FBulletEditor::GetBulletEditorSettingInstance()->SetPlayer(Player);
	}

	//Enemy 생성
	FSoftObjectPath EnemyMaterialPath = TEXT("Material'/Engine/EditorMaterials/WidgetMaterial_X.WidgetMaterial_X'");
	TSoftObjectPtr<UMaterial> EnemyMaterialObject(EnemyMaterialPath);
	Enemy = CreateDanmakuActor(FVector(0, -4000, 0), EnemyMaterialObject.Get(), TEXT("Enemy"));
	if (IsValid(Enemy))
	{
		FBulletEditor::GetBulletEditorSettingInstance()->SetEnemy(Enemy);
	}
		
	//벽 생성
	FSoftObjectPath CubeObjectPath = TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'");
	TSoftObjectPtr<UStaticMesh> CubeObject(CubeObjectPath);
	
	FSoftObjectPath WhiteMaterialPath = TEXT("Material'/Engine/EditorMaterials/WidgetMaterial.WidgetMaterial'");
	TSoftObjectPtr<UMaterial> WhiteMaterialObject(WhiteMaterialPath);

	//50.0f가 엔진에서 제공하는 큐브의 한 변 길이
	auto CreateWall = [=](UStaticMesh* InStaticMesh, UMaterial* InMaterial, FVector InLocation, FVector InBoxSize) -> AActor* {
		FActorSpawnParameters ActorSpawnParamters = FActorSpawnParameters();
		ActorSpawnParamters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//아직 루트 컴포넌트가 없기 때문에 월드에 좌표를 찍을수가 없음.
		AActor* Actor = PreviewScene->GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), FVector::ZeroVector, FRotator(), ActorSpawnParamters);
		
		if (IsValid(Actor))
		{
			UBoxComponent* BoxComponent = NewObject<UBoxComponent>(Actor, UBoxComponent::StaticClass(), FName("BoxComponent"));
			if (BoxComponent)
			{
				BoxComponent->RegisterComponent();
				BoxComponent->SetBoxExtent(InBoxSize);
				Actor->SetRootComponent(BoxComponent);
			}

			UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(Actor, UStaticMeshComponent::StaticClass(), FName("StaticMeshComponent"));
			if (StaticMeshComponent)
			{
				StaticMeshComponent->RegisterComponent();
				StaticMeshComponent->SetStaticMesh(InStaticMesh);

				UMaterial* Material = InMaterial;
				if (IsValid(Material) == false)
				{
					Material = NewObject<UMaterial>(Actor, UMaterial::StaticClass(), FName("Material"));

					UMaterialExpressionConstant3Vector* BaseColorFactorNode = NewObject<UMaterialExpressionConstant3Vector>();
					BaseColorFactorNode->Constant = FColor::White;
					Material->BaseColor.Connect(0, BaseColorFactorNode);
					Material->PostEditChange();
				}
				StaticMeshComponent->SetMaterial(0, Material);
				StaticMeshComponent->AttachToComponent(Actor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
				StaticMeshComponent->SetRelativeScale3D(InBoxSize / 50.0f);
			}
		     
			Actor->SetActorLocation(InLocation);

			Actor->Tags.Add(TEXT("Wall"));
		}

		return Actor;
	};

	FVector2D BoxSize = FVector2D(85.0f, 105.0f);
	FBulletEditor::GetBulletEditorSettingInstance()->SetWallSize(BoxSize);

	WallArray.Empty();
	//Width
	WallArray.Add(CreateWall(CubeObject.Get(), WhiteMaterialObject.Get(), FVector(0.0f, BoxSize.Y  * 50.0f, 0.0f), FVector(BoxSize.X * 50.0f, 50.0f, 50.0f)));
	WallArray.Add(CreateWall(CubeObject.Get(), WhiteMaterialObject.Get(), FVector(0.0f, -1.0f * BoxSize.Y * 50.0f, 0.0f), FVector(BoxSize.X * 50.0f, 50.0f, 50.0f)));
	//Height
	WallArray.Add(CreateWall(CubeObject.Get(), WhiteMaterialObject.Get(), FVector(BoxSize.X  * 50.0f, 0.0f, 0.0f), FVector(50.0f, BoxSize.Y * 50.0f, 50.0f)));
	WallArray.Add(CreateWall(CubeObject.Get(), WhiteMaterialObject.Get(), FVector(- BoxSize.X  * 50.0f, 0.0f, 0.0f), FVector(50.0f, BoxSize.Y * 50.0f, 50.0f)));

	if (PreviewScene != nullptr)
	{
		PreviewScene->GetWorld()->bBegunPlay = bIsSimulateInEditorViewport;
		PreviewScene->GetWorld()->bShouldSimulatePhysics = bIsSimulateInEditorViewport;
	}
}

void FBulletEditorViewport::Tick(float DeltaTime)
{
	FEditorViewportClient::Tick(DeltaTime);
	
	if (BulletEditorPlayType == EBulletEditorPlayType::PLAY)
	{
		if (PreviewScene != nullptr && PreviewScene->GetWorld() != nullptr)
		{
			PreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaTime);
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
					if (ConsideredActor->IsA(ADanmakuBullet::StaticClass()))
					{
						FBulletEditor::SetDetailViewObject(ConsideredActor);
					}
					else
					{
						FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
						if (ConsideredActor->ActorHasTag(TEXT("Player")))
						{
							PropertyEditorModule.RegisterCustomClassLayout(TEXT("BulletEditorSetting"), FOnGetDetailCustomizationInstance::CreateStatic(&BulletEditorDetailCustomization::MakeInstance, BulletEditorDetailCustomization::EActorType::PLAYER));
						}
						else if (ConsideredActor->ActorHasTag(TEXT("Enemy")))
						{
							PropertyEditorModule.RegisterCustomClassLayout(TEXT("BulletEditorSetting"), FOnGetDetailCustomizationInstance::CreateStatic(&BulletEditorDetailCustomization::MakeInstance, BulletEditorDetailCustomization::EActorType::ENEMY));
						}
						else if (ConsideredActor->ActorHasTag(TEXT("Wall")))
						{
							PropertyEditorModule.RegisterCustomClassLayout(TEXT("BulletEditorSetting"), FOnGetDetailCustomizationInstance::CreateStatic(&BulletEditorDetailCustomization::MakeInstance, BulletEditorDetailCustomization::EActorType::WALL));
						}
						FBulletEditor::SetDetailViewObject(FBulletEditor::GetBulletEditorSettingInstance());
					}
				}
			}
		}
	}
}

bool FBulletEditorViewport::InputKey(FViewport* InViewport, int32 ControllerId, FKey Key, EInputEvent Event, float AmountDepressed /*= 1.f*/, bool bGamepad /*= false*/)
{
	if ((Key == EKeys::MouseScrollUp || Key == EKeys::MouseScrollDown || Key == EKeys::Add || Key == EKeys::Subtract) && (Event == IE_Pressed || Event == IE_Repeat) && IsOrtho())
	{
		FViewportCameraTransform& ViewTransform = GetViewTransform();
		FBulletEditor::GetBulletEditorSettingInstance()->SetCameraDistance(ViewTransform.GetOrthoZoom());
	}

	return FEditorViewportClient::InputKey(InViewport, ControllerId, Key, Event, AmountDepressed, bGamepad);
}

void FBulletEditorViewport::Play()
{
	if (BulletEditorPlayType == EBulletEditorPlayType::STOP)
	{
		SaveInitData();

		if (PreviewScene && PreviewScene->GetWorld())
		{
			if (Player)
			{
				PreviewScene->GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, Player, &ADanmakuActor::PlayPattern, FBulletEditor::GetBulletEditorSettingInstance()->GetBulletSpawnPerSecond(), true);
			}
		}

		//#todo : 추후에 총알 설정하는 코드 넣으면 사용할것.
		/*
		if (Enemy)
		{
			Enemy->PlayPattern();
		}
		*/
	}

	BulletEditorPlayType = EBulletEditorPlayType::PLAY;
}

void FBulletEditorViewport::Stop()
{
	BulletEditorPlayType = EBulletEditorPlayType::STOP;

	ResetInitData();

	if (PreviewScene != nullptr && PreviewScene->GetWorld() != nullptr)
	{
		UWorld* World = PreviewScene->GetWorld();
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			AActor* Actor = *It;
			if (!Actor->IsPendingKillPending())
			{
				if (Actor->IsA(ADanmakuBullet::StaticClass()))
				{
					Actor->Destroy();
				}
			}
		}

		World->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}
	
	
}

void FBulletEditorViewport::Pause()
{
	BulletEditorPlayType = EBulletEditorPlayType::PAUSE;
}


void FBulletEditorViewport::UpdateWallSize()
{
	auto UpdateWall = [=](AActor* InWall, FVector InLocation, FVector InBoxSize)
	{
		if (IsValid(InWall))
		{
			InWall->SetActorLocation(InLocation);

			UStaticMeshComponent* StaticMeshComponent = InWall->FindComponentByClass<UStaticMeshComponent>();
			if (IsValid(StaticMeshComponent))
			{
				StaticMeshComponent->SetRelativeScale3D(InBoxSize / 50.0f);
			}

			UBoxComponent* BoxComponent = InWall->FindComponentByClass<UBoxComponent>();
			if (IsValid(BoxComponent))
			{
				BoxComponent->SetBoxExtent(InBoxSize);
			}
		}
	};

	FVector2D BoxSize = FBulletEditor::GetBulletEditorSettingInstance()->GetWallSize();

	//Bottom
	if (WallArray.IsValidIndex(0))
	{
		if (IsValid(WallArray[0]))
		{
			UpdateWall(WallArray[0], FVector(0.0f, BoxSize.Y * 50.0f, 0.0f), FVector(BoxSize.X * 50.0f, 50.0f, 50.0f));
		}
	}

	//Top
	if (WallArray.IsValidIndex(1))
	{
		if (IsValid(WallArray[1]))
		{
			UpdateWall(WallArray[1], FVector(0.0f, -1.0f * BoxSize.Y * 50.0f, 0.0f), FVector(BoxSize.X * 50.0f, 50.0f, 50.0f));
		}
	}

	//left
	if (WallArray.IsValidIndex(2))
	{
		if (IsValid(WallArray[2]))
		{
			UpdateWall(WallArray[2], FVector(BoxSize.X * 50.0f, 0.0f, 0.0f), FVector(50.0f, BoxSize.Y * 50.0f, 50.0f));
		}
	}

	//right
	if (WallArray.IsValidIndex(3))
	{
		if (IsValid(WallArray[3]))
		{
			UpdateWall(WallArray[3], FVector(-BoxSize.X * 50.0f, 0.0f, 0.0f), FVector(50.0f, BoxSize.Y * 50.0f, 50.0f));
		}
	}
}

void FBulletEditorViewport::SaveInitData()
{
	PlayerSaveData = Player;
	EnemySaveData = Enemy;
}

void FBulletEditorViewport::ResetInitData()
{
	Player = PlayerSaveData;
	Enemy = EnemySaveData;
}

