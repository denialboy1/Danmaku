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
	virtual void ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY);

	void Play();
	void Stop();
	void Pause();

private:
	void SaveInitData();
public:
	FPreviewScene* PreviewScene;

	//#todo : ���Ŀ� �ʱ�ȭ ��Ű�� ��� ����.(����� ��ǥ�� �ǵ���)
	TMap<FString, FVector> InitDataList;
private:
	UPROPERTY(Transient)
	EBulletEditorPlayType BulletEditorPlayType = EBulletEditorPlayType::STOP;

	FVector2D BorderSize;
};
