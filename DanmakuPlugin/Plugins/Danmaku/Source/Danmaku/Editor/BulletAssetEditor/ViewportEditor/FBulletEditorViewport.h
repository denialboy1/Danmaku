// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

UENUM(BlueprintType)
enum class EBulletEditorPlayType : uint8
{
	STOP = 0,
	PLAY,
	PAUSE,
};


class FBulletEditorViewport : public FEditorViewportClient
{
public:
	FBulletEditorViewport(FPreviewScene* InPreviewScene);

	virtual void Tick(float DeltaTime) override;

	void Play();
	void Stop();
	void Pause();

private:
	void SaveInitData();
public:
	FPreviewScene* PreviewScene;

	class AActor* Enemy;
	class AActor* Bullet;

	//#todo : ���Ŀ� �ʱ�ȭ ��Ű�� ��� ����.(����� ��ǥ�� �ǵ���)
	TMap<FString, FVector> InitDataList;
private:
	UPROPERTY(Transient)
	EBulletEditorPlayType BulletEditorPlayType = EBulletEditorPlayType::STOP;
};
