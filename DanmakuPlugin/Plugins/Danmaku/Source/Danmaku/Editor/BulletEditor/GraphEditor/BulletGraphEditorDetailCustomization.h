// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDetailCustomization.h"

class DANMAKU_API BulletGraphEditorDetailCustomization : public IDetailCustomization
{
public:

	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

};
