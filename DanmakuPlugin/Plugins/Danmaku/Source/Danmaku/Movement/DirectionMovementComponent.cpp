// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionMovementComponent.h"


void UDirectionMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Velocity = FVector(1.0f, 0.0f, 0.0f);
}

void UDirectionMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveUpdatedComponent(Velocity, FRotator::ZeroRotator, false);
}
