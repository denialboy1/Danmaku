// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include "UObject/ConstructorHelpers.h"
// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UStaticMeshComponent* SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

