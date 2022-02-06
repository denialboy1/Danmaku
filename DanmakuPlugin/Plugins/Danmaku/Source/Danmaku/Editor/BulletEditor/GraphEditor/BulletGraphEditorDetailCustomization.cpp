// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletGraphEditorDetailCustomization.h"
#include "BulletEdGraphNode.h"

#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"


TSharedRef<IDetailCustomization> BulletGraphEditorDetailCustomization::MakeInstance()
{
	return MakeShareable(new BulletGraphEditorDetailCustomization);
}

void BulletGraphEditorDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//Default로는 모든 카테고리를 보여줌. ForceHideCategory로 보여주고 싶지 않은 속성을 숨긴다.

	if (DetailBuilder.GetBaseClass() == UBulletEdGraphNode::StaticClass())
	{
		DetailBuilder.HideCategory(TEXT("BulletAttributeList"));

		//커스텀해서 보여주고 싶은 방식을 커스텀하고 싶을 때 여기다 추가.
		IDetailCategoryBuilder& DetailCategoryBuilder = DetailBuilder.EditCategory(TEXT("AttributeName"), FText::FromString(TEXT("Attribute")));
		

		TArray<TWeakObjectPtr<UObject>> ObjectArray;
		DetailBuilder.GetObjectsBeingCustomized(ObjectArray);

		UObject* SelectObject = nullptr;
		if (ObjectArray.IsValidIndex(0))
		{
			SelectObject = ObjectArray[0].Get();
		}
		
		UBulletEdGraphNode* BulletEdGraphNode = Cast<UBulletEdGraphNode>(SelectObject);

		for (auto BulletAttribute : BulletEdGraphNode->GetBulletAttributeList())
		{
			DetailCategoryBuilder.AddCustomRow(FText::FromString(TEXT("AttributeName"))).ValueContent()
				[
					SNew(STextBlock).Text(FText::FromName(BulletAttribute.AttributeName))
				];
		}
		
		
	}
}
