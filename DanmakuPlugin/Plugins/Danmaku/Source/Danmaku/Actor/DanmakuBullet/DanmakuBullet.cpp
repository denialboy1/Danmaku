// Fill out your copyright notice in the Description page of Project Settings.

#include "DanmakuBullet.h"

#include "Danmaku/Movement/BulletMovementComponent.h"

// Sets default values
ADanmakuBullet::ADanmakuBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADanmakuBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADanmakuBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

