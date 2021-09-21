// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletAssetActions.h"
#include "Danmaku/Actor/DanmakuBullet/DanmakuBullet.h"
#include "Danmaku/Editor/BulletEditor/BulletEditor.h"


FBulletAssetActions::FBulletAssetActions(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FText FBulletAssetActions::GetName() const
{
	return FText::FromString("Bullet");
}

FColor FBulletAssetActions::GetTypeColor() const
{
	return FColor(125, 125, 125);
}

UClass* FBulletAssetActions::GetSupportedClass() const
{
	return ADanmakuBullet::StaticClass();
}

uint32 FBulletAssetActions::GetCategories()
{
	return MyAssetCategory;
}

void FBulletAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	//에셋 생성창
	FBulletEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
}
