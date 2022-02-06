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
		DetailBuilder.HideCategory(TEXT("BulletAttributeList"));

		//Ŀ�����ؼ� �����ְ� ���� ����� Ŀ�����ϰ� ���� �� ����� �߰�.
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
