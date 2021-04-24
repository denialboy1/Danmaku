// Fill out your copyright notice in the Description page of Project Settings.


#include "Danmaku/Editor/FBulletDetails.h"
//#include "Danmaku/Editor/BulletAsset.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

TSharedRef<IDetailCustomization> FBulletDetails::MakeInstance()
{
	return MakeShareable(new FBulletDetails);
}

void FBulletDetails::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	IDetailCategoryBuilder& OptionsCategory = DetailLayout.EditCategory("Select", FText::FromString(""), ECategoryPriority::Important);
	OptionsCategory.AddCustomRow(FText::FromString("Options"))
		.WholeRowContent()
		[
			SNew(STextBlock).Text(FText::FromString("Option 2"))
		];

}
