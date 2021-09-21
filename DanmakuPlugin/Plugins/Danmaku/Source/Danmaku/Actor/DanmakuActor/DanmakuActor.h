// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DanmakuActor.generated.h"

UCLASS()
class DANMAKU_API ADanmakuActor : public AActor
{
	GENERATED_BODY()

private:
	//#todo : 임시 코드
	UClass* BulletClass;
public:	
	// Sets default values for this actor's properties
	ADanmakuActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlayPattern();
};
