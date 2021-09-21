// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"




class FBulletEditorViewport : public FEditorViewportClient
{
public:
	enum class EBulletEditorPlayType
	{
		STOP,
		PLAY,
		PAUSE,
	};

public:
	FBulletEditorViewport(FPreviewScene* InPreviewScene);

	virtual void Tick(float DeltaTime) override;
	virtual void ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;
	virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent Event, float AmountDepressed = 1.f, bool bGamepad = false) override;
	virtual void SetIsSimulateInEditorViewport(bool bInIsSimulateInEditorViewport) override { bIsSimulateInEditorViewport = bInIsSimulateInEditorViewport; }

	void Play();
	void Stop();
	void Pause();

	void UpdateWallSize();
private:
	void SaveInitData();
	void ResetInitData();
public:
	FPreviewScene* PreviewScene;

	//#todo : 추후에 초기화 시키는 방법 개선.(현재는 좌표만 되돌림)
	TMap<FString, FVector> InitDataList;
private:
	FTimerHandle SpawnTimerHandle;

	class ADanmakuActor* Player;
	class ADanmakuActor* Enemy;

	class ADanmakuActor* PlayerSaveData;
	class ADanmakuActor* EnemySaveData;

	TArray<AActor*> WallArray;

	UPROPERTY(Transient)
	EBulletEditorPlayType BulletEditorPlayType = EBulletEditorPlayType::STOP;

	FVector2D BorderSize;
};
