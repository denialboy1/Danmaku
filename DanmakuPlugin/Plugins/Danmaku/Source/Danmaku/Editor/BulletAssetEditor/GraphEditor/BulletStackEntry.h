// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct FBulletStackEntry 
{
public:
	// ���� ���� �������� ���� �����ͷ� ��������!, �׷��� ���� �Լ��� �� �������� �����Ҽ� �ְ� ����
	static TSharedRef<FBulletStackEntry> Make()
	{
		return MakeShareable(new FBulletStackEntry());
	}
public:
	FString BulletAttribute;
};
