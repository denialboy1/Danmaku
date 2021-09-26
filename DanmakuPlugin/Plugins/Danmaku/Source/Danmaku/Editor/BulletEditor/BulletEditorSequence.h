// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "MovieSceneSequence.h"
#include "BulletEditorSequence.generated.h"

class UMovieScene;
/**
 * 
 */
UCLASS(BlueprintType, MinimalAPI)
class UBulletEditorSequence : public UMovieSceneSequence
{
	GENERATED_UCLASS_BODY()

public:
	void Initialize(UMovieScene* InMovieScene);

	//~ UMovieSceneSequence interface
	virtual void BindPossessableObject(const FGuid& ObjectId, UObject& PossessedObject, UObject* Context) override;
	virtual bool CanPossessObject(UObject& Object, UObject* InPlaybackContext) const override;
	virtual UMovieScene* GetMovieScene() const override;
	virtual UObject* GetParentObject(UObject* Object) const override;
	virtual void UnbindPossessableObjects(const FGuid& ObjectId) override;

private:
	/** Pointer to the movie scene that controls this sequence. */
	UPROPERTY()
	UMovieScene* MovieScene;
};
