// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "BulletAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class DANMAKU_API UBulletAssetFactory : public UFactory
{
	GENERATED_BODY()

	UBulletAssetFactory();
public:

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
