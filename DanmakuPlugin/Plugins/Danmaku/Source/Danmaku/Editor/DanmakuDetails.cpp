// Fill out your copyright notice in the Description page of Project Settings.


#include "DanmakuDetails.h"
#include "DetailLayoutBuilder.h"

TSharedRef<IDetailCustomization> FDanmakuDetails::MakeInstance()
{
	return MakeShareable(new FDanmakuDetails());
}

void FDanmakuDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *DetailBuilder.GetBaseClass()->GetName());
}
