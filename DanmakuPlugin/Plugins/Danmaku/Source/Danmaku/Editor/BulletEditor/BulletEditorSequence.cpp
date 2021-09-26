// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletEditorSequence.h"

UBulletEditorSequence::UBulletEditorSequence(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MovieScene(nullptr)
{ }

void UBulletEditorSequence::Initialize(UMovieScene* InMovieScene)
{
	MovieScene = InMovieScene;
}

void UBulletEditorSequence::BindPossessableObject(const FGuid& ObjectId, UObject& PossessedObject, UObject* Context)
{

}

bool UBulletEditorSequence::CanPossessObject(UObject& Object, UObject* InPlaybackContext) const
{
	return false;
}

UMovieScene* UBulletEditorSequence::GetMovieScene() const
{
	checkf(MovieScene != nullptr, TEXT("BulletEditor Sequence not initialized"));
	return MovieScene;
}

UObject* UBulletEditorSequence::GetParentObject(UObject* Object) const
{
	return nullptr;
}

void UBulletEditorSequence::UnbindPossessableObjects(const FGuid& ObjectId)
{

}
