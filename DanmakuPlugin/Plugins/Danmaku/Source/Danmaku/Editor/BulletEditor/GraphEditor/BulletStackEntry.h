// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct FBulletStackEntry 
{
public:
	// 새로 만든 아이템은 공유 포인터로 만들어야함!, 그래서 전역 함수로 이 아이템을 생성할수 있게 구현
	static TSharedRef<FBulletStackEntry> Make()
	{
		return MakeShareable(new FBulletStackEntry());
	}
public:
	FString BulletAttribute;
};
