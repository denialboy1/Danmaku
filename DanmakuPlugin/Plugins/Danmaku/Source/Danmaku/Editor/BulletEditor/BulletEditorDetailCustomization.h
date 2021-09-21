// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IDetailCustomization.h"

class DANMAKU_API BulletEditorDetailCustomization : public IDetailCustomization
{
public:
	enum class EActorType
	{
		PLAYER,
		ENEMY,
		WALL,
		GAMESETTING
	};

public:
	static TSharedRef<IDetailCustomization> MakeInstance(EActorType ActorType);

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
private:
	class UBulletEditorSetting* BulletEditorSetting;

	static EActorType CurrentActorType;
private:
	TOptional<float> GetPlayerLocationX() const;
	TOptional<float> GetPlayerLocationY() const;
	TOptional<float> GetPlayerLocationZ() const;

	TOptional<float> GetEnemyLocationX() const;
	TOptional<float> GetEnemyLocationY() const;
	TOptional<float> GetEnemyLocationZ() const;

	void OnSetTransformAxis(float NewValue, ETextCommit::Type CommitInfo, EAxisList::Type Axis, EActorType ActorType );
	void AddCustomDetailPropertyDanmakuActor(
		IDetailLayoutBuilder& DetailBuilder,
		FString InName,
		TOptional<float>(BulletEditorDetailCustomization::* InFuncLocationX)() const,
		TOptional<float>(BulletEditorDetailCustomization::* InFuncLocationY)() const,
		TOptional<float>(BulletEditorDetailCustomization::* InFuncLocationZ)() const,
		EActorType ActorType);
};
