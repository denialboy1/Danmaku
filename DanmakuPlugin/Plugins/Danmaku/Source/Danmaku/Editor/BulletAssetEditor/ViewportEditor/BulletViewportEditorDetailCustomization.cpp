// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletViewportEditorDetailCustomization.h"
#include "DetailLayoutBuilder.h"

TSharedRef<IDetailCustomization> BulletViewportEditorDetailCustomization::MakeInstance()
{
	return MakeShareable(new BulletViewportEditorDetailCustomization);
}

void BulletViewportEditorDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<FName> CategoryNameArray;
	DetailBuilder.GetCategoryNames(CategoryNameArray);

	for (auto Name : CategoryNameArray)
	{
		if (Name == TEXT("TransformCommon"))
		{
			continue;
		}
		DetailBuilder.HideCategory(Name);
	}
}
