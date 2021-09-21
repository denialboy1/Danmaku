// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletAssetFactory.h"
#include "Danmaku/Actor/DanmakuBullet/DanmakuBullet.h"

UBulletAssetFactory::UBulletAssetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = ADanmakuBullet::StaticClass();
}

UObject* UBulletAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	ADanmakuBullet* NewObjectAsset = NewObject<ADanmakuBullet>(InParent, Class, Name, Flags | RF_Transactional);
	return NewObjectAsset;
}

