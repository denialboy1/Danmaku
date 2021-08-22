// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletGraphEditorDetailCustomization.h"
#include "BulletEdGraphNode.h"

#include "DetailLayoutBuilder.h"


TSharedRef<IDetailCustomization> BulletGraphEditorDetailCustomization::MakeInstance()
{
	return MakeShareable(new BulletGraphEditorDetailCustomization);
}

void BulletGraphEditorDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//Default�δ� ��� ī�װ��� ������. ForceHideCategory�� �����ְ� ���� ���� �Ӽ��� �����.

	if (DetailBuilder.GetBaseClass() == UBulletEdGraphNode::StaticClass())
	{
		//Ŀ�����ؼ� �����ְ� ���� ����� Ŀ�����ϰ� ���� �� ����� �߰�.
	}
}
