// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletAssetFactory.h"
#include "Danmaku/Actor/DanmakuBullet/DanmakuBullet.h"
#include "Danmaku/Editor/BulletEditor/BulletFactory.h"

UBulletAssetFactory::UBulletAssetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UBulletFactory::StaticClass();
}

UObject* UBulletAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(Class->IsChildOf(UBulletFactory::StaticClass()));
	return NewObject<UBulletFactory>(InParent, Class, Name, Flags);;
}

