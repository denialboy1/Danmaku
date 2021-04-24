// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletAssetFactory.h"
#include "Danmaku/Bullet/Bullet.h"

UBulletAssetFactory::UBulletAssetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = ABullet::StaticClass();
}

UObject* UBulletAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	ABullet* NewObjectAsset = NewObject<ABullet>(InParent, Class, Name, Flags | RF_Transactional);
	return NewObjectAsset;
}

