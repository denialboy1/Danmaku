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
	//Default�δ� ��� ī�װ��� ������. ForceHideCategory�� �����ְ� ���� ���� �Ӽ��� �����.

	if (DetailBuilder.GetBaseClass() == UBulletEdGraphNode::StaticClass())
	{
		DetailBuilder.HideCategory(TEXT("MoveAttributeList"));
		DetailBuilder.HideCategory(TEXT("SpecialAttributeList"));
		TArray<TWeakObjectPtr<UObject>> ObjectArray;
		DetailBuilder.GetObjectsBeingCustomized(ObjectArray);

		UObject* SelectObject = nullptr;
		if (ObjectArray.IsValidIndex(0))
		{
			SelectObject = ObjectArray[0].Get();
		}
		
		UBulletEdGraphNode* BulletEdGraphNode = Cast<UBulletEdGraphNode>(SelectObject);

		IDetailCategoryBuilder& DetailCategoryBuilder = DetailBuilder.EditCategory(TEXT("Attribute"));

		//DetailCategoryBuilder
		DetailCategoryBuilder.AddGroup(TEXT("MovementAttribute"), FText::FromString(TEXT("MoveAttributeName")));
		for (auto BulletAttribute : BulletEdGraphNode->GetMoveAttributeList())
		{
			DetailCategoryBuilder.AddCustomRow(FText::FromString(TEXT("MoveAttributeName"))).ValueContent()
				[
					SNew(STextBlock).Text(FText::FromName(BulletAttribute.AttributeName))
				];
		}

		DetailCategoryBuilder.AddGroup(TEXT("SpecialAttributeName"), FText::FromString(TEXT("SpecialAttributeName")));
		for (auto BulletAttribute : BulletEdGraphNode->GetSpecialAttributeList())
		{
			DetailCategoryBuilder.AddCustomRow(FText::FromString(TEXT("SpecialAttributeName"))).ValueContent()
				[
					SNew(STextBlock).Text(FText::FromName(BulletAttribute.AttributeName))
				];
		}
		
	}
}
