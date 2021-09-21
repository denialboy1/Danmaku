// Fill out your copyright notice in the Description page of Project Settings.


#include "DanmakuActor.h"

// Sets default values
ADanmakuActor::ADanmakuActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UStaticMeshComponent* StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	//#todo : 임시 생성 코드
	FSoftObjectPath TempDirectionBulletPath = TEXT("Class'/Danmaku/Bullet/Direction/DirectionBullet.DirectionBullet_C'");
	TSoftObjectPtr<UClass> TempDirectionBulletObject(TempDirectionBulletPath);
	BulletClass = TempDirectionBulletObject.LoadSynchronous();
}

// Called when the game starts or when spawned
void ADanmakuActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADanmakuActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADanmakuActor::PlayPattern()
{
	
	//#todo : 2021-09-19 패턴정보를 가져와서 실행시키는 기능 추가할것
	// 지금은 임시로 Timer를 통해 총알 액터 생성하는 코드를 넣어둠
	//임시 코드
	FActorSpawnParameters ActorSpawnParamters = FActorSpawnParameters();
	ActorSpawnParamters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (BulletClass != nullptr)
	{
		if (IsValid(GetWorld()))
		{
			AActor* Actor = GetWorld()->SpawnActor<AActor>(BulletClass, GetActorLocation(), FRotator(0.f, 180.f, 0.f), ActorSpawnParamters);
			Actor->SetActorScale3D(FVector(10.0f, 10.f, 10.f));
		}
	}
}

