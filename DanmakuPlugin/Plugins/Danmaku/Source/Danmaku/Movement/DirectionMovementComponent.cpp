// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionMovementComponent.h"

void UDirectionMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult Hit;
	MoveUpdatedComponent(FVector(1, 0, 0), FRotator(0, 0, 0), false);
}
