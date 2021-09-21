// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletEditorDetailCustomization.h"
#include "DetailLayoutBuilder.h"
#include "BulletEditorSetting.h"
#include "DetailCategoryBuilder.h"
#include "Widgets/Input/SVectorInputBox.h"
#include "Widgets/Text/STextBlock.h"
#include "DetailWidgetRow.h"
#include "BulletEditor.h"

BulletEditorDetailCustomization::EActorType BulletEditorDetailCustomization::CurrentActorType;

TSharedRef<IDetailCustomization> BulletEditorDetailCustomization::MakeInstance(EActorType ActorType)
{
	CurrentActorType = ActorType;
	return MakeShareable(new BulletEditorDetailCustomization);
}

void BulletEditorDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> ObjectArray;
	DetailBuilder.GetObjectsBeingCustomized(ObjectArray);

	UObject* Object = nullptr;
	for (auto WeakObject : ObjectArray)
	{
		Object = WeakObject.Get();
	}
	
	BulletEditorSetting = Cast<UBulletEditorSetting>(Object);

	if (BulletEditorSetting == nullptr)
	{
		BulletEditorSetting = FBulletEditor::GetBulletEditorSettingInstance();
	}

	if (CurrentActorType == EActorType::WALL)
	{
		DetailBuilder.HideProperty(TEXT("BulletSpawnPerSecond"));
		DetailBuilder.HideProperty(TEXT("CameraDistance"));
	}
	else if (CurrentActorType == EActorType::PLAYER)
	{
		DetailBuilder.HideProperty(TEXT("WallSize"));
		DetailBuilder.HideProperty(TEXT("CameraDistance"));
		AddCustomDetailPropertyDanmakuActor(DetailBuilder, TEXT("Player"), &BulletEditorDetailCustomization::GetPlayerLocationX, &BulletEditorDetailCustomization::GetPlayerLocationY, &BulletEditorDetailCustomization::GetPlayerLocationZ, EActorType::PLAYER);
	}
	else if (CurrentActorType == EActorType::ENEMY)
	{
		DetailBuilder.HideProperty(TEXT("BulletSpawnPerSecond"));
		DetailBuilder.HideProperty(TEXT("WallSize"));
		DetailBuilder.HideProperty(TEXT("CameraDistance"));
		AddCustomDetailPropertyDanmakuActor(DetailBuilder, TEXT("Enemy"), &BulletEditorDetailCustomization::GetEnemyLocationX, &BulletEditorDetailCustomization::GetEnemyLocationY, &BulletEditorDetailCustomization::GetEnemyLocationZ, EActorType::ENEMY);
	}
	else
	{
		AddCustomDetailPropertyDanmakuActor(DetailBuilder, TEXT("Player"), &BulletEditorDetailCustomization::GetPlayerLocationX, &BulletEditorDetailCustomization::GetPlayerLocationY, &BulletEditorDetailCustomization::GetPlayerLocationZ, EActorType::PLAYER);
		AddCustomDetailPropertyDanmakuActor(DetailBuilder, TEXT("Enemy"), &BulletEditorDetailCustomization::GetEnemyLocationX, &BulletEditorDetailCustomization::GetEnemyLocationY, &BulletEditorDetailCustomization::GetEnemyLocationZ, EActorType::ENEMY);
	}
}

TOptional<float> BulletEditorDetailCustomization::GetPlayerLocationX() const
{
	if (BulletEditorSetting && BulletEditorSetting->GetPlayer())
	{
		return BulletEditorSetting->GetPlayer()->GetActorLocation().X;
	}

	return 0.0f;
}

TOptional<float> BulletEditorDetailCustomization::GetPlayerLocationY() const
{
	if (BulletEditorSetting && BulletEditorSetting->GetPlayer())
	{
		return BulletEditorSetting->GetPlayer()->GetActorLocation().Y;
	}

	return 0.0f;
}

TOptional<float> BulletEditorDetailCustomization::GetPlayerLocationZ() const
{
	if (BulletEditorSetting && BulletEditorSetting->GetPlayer())
	{
		return BulletEditorSetting->GetPlayer()->GetActorLocation().Z;
	}

	return 0.0f;
}

TOptional<float> BulletEditorDetailCustomization::GetEnemyLocationX() const
{
	if (BulletEditorSetting && BulletEditorSetting->GetEnemy())
	{
		return BulletEditorSetting->GetEnemy()->GetActorLocation().X;
	}

	return 0.0f;
}

TOptional<float> BulletEditorDetailCustomization::GetEnemyLocationY() const
{
	if (BulletEditorSetting && BulletEditorSetting->GetEnemy())
	{
		return BulletEditorSetting->GetEnemy()->GetActorLocation().Y;
	}

	return 0.0f;
}

TOptional<float> BulletEditorDetailCustomization::GetEnemyLocationZ() const
{
	if (BulletEditorSetting && BulletEditorSetting->GetEnemy())
	{
		return BulletEditorSetting->GetEnemy()->GetActorLocation().Z;
	}

	return 0.0f;
}

void BulletEditorDetailCustomization::OnSetTransformAxis(float NewValue, ETextCommit::Type CommitInfo, EAxisList::Type Axis, EActorType ActorType)
{
	if (ActorType == EActorType::PLAYER)
	{
		if (Axis == EAxisList::X)
		{
			if (BulletEditorSetting && BulletEditorSetting->GetPlayer())
			{
				FVector Location = BulletEditorSetting->GetPlayer()->GetActorLocation();
				Location.X = NewValue;
				BulletEditorSetting->GetPlayer()->SetActorLocation(Location);
			}
		}
		else if (Axis == EAxisList::Y)
		{
			if (BulletEditorSetting && BulletEditorSetting->GetPlayer())
			{
				FVector Location = BulletEditorSetting->GetPlayer()->GetActorLocation();
				Location.Y = NewValue;
				BulletEditorSetting->GetPlayer()->SetActorLocation(Location);
			}
		}
		else if (Axis == EAxisList::Z)
		{
			if (BulletEditorSetting && BulletEditorSetting->GetPlayer())
			{
				FVector Location = BulletEditorSetting->GetPlayer()->GetActorLocation();
				Location.Z = NewValue;
				BulletEditorSetting->GetPlayer()->SetActorLocation(Location);
			}
		}
	}
	else if (ActorType == EActorType::ENEMY)
	{
		if (Axis == EAxisList::X)
		{
			if (BulletEditorSetting && BulletEditorSetting->GetEnemy())
			{
				FVector Location = BulletEditorSetting->GetEnemy()->GetActorLocation();
				Location.X = NewValue;
				BulletEditorSetting->GetEnemy()->SetActorLocation(Location);
			}
		}
		else if (Axis == EAxisList::Y)
		{
			if (BulletEditorSetting && BulletEditorSetting->GetEnemy())
			{
				FVector Location = BulletEditorSetting->GetEnemy()->GetActorLocation();
				Location.Y = NewValue;
				BulletEditorSetting->GetEnemy()->SetActorLocation(Location);
			}
		}
		else if (Axis == EAxisList::Z)
		{
			if (BulletEditorSetting && BulletEditorSetting->GetEnemy())
			{
				FVector Location = BulletEditorSetting->GetEnemy()->GetActorLocation();
				Location.Z = NewValue;
				BulletEditorSetting->GetEnemy()->SetActorLocation(Location);
			}
		}
	}
}

void BulletEditorDetailCustomization::AddCustomDetailPropertyDanmakuActor(
	IDetailLayoutBuilder& DetailBuilder,
	FString InName,
	TOptional<float>(BulletEditorDetailCustomization::* InFuncLocationX)() const,
	TOptional<float>(BulletEditorDetailCustomization::* InFuncLocationY)() const,
	TOptional<float>(BulletEditorDetailCustomization::* InFuncLocationZ)() const,
	EActorType ActorType)
{
	IDetailCategoryBuilder& DetailCategoryBuilder = DetailBuilder.EditCategory("BulletEditorSetting");

	DetailCategoryBuilder.AddCustomRow(FText::FromString(InName), false)
		.NameContent()
		[
			SNew(STextBlock)
			.Text(FText::FromString(InName + TEXT(" Location")))
		]
	.ValueContent().HAlign(HAlign_Fill)
		[
			SNew(SVectorInputBox)
			.X(this, InFuncLocationX)
		.Y(this, InFuncLocationY)
		.Z(this, InFuncLocationZ)
		.bColorAxisLabels(true)
		.AllowResponsiveLayout(true)
		.AllowSpin(true)
		.OnXChanged(this, &BulletEditorDetailCustomization::OnSetTransformAxis, ETextCommit::Default, EAxisList::X, ActorType)
		.OnYChanged(this, &BulletEditorDetailCustomization::OnSetTransformAxis, ETextCommit::Default, EAxisList::Y, ActorType)
		.OnZChanged(this, &BulletEditorDetailCustomization::OnSetTransformAxis, ETextCommit::Default, EAxisList::Z, ActorType)
		];

}
