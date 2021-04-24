// Fill out your copyright notice in the Description page of Project Settings.


#include "FBulletAssetActions.h"
#include "Danmaku/Bullet/Bullet.h"
#include "Danmaku/Editor/BulletAssetEditor.h"


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
	return ABullet::StaticClass();
}

uint32 FBulletAssetActions::GetCategories()
{
	return MyAssetCategory;
}

void FBulletAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	//FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
	//에셋 생성창
	FBulletAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
}
