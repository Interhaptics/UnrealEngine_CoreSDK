/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "HapticSource.h"

int AHapticSource::GetID()
{
	return hapticEffectID;
}

// Sets default values
AHapticSource::AHapticSource()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHapticSource::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (HapticEffect == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HAPS NOT ASSIGNED")));
		return;
	}

	hapticEffectID = InterhapticsEngine::AddHM(TCHAR_TO_ANSI(*(HapticEffect->Text.ToString())));
}

// Called every frame
void AHapticSource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHapticSource::Play()
{
	InterhapticsEngine::PlayEvent(hapticEffectID, (double)(VibrationOffset - GetWorld()->GetTimeSeconds()), (double)TextureOffset, (double)StiffnessOffset);
}

void AHapticSource::Stop()
{
	InterhapticsEngine::StopEvent(hapticEffectID);
}

void AHapticSource::SetTargets(ETargetEnum Target)
{
	if (hapticEffectID == -1)
	{
		return;
	}

	InterhapticsEngine::RemoveAllTargetsFromEvent(hapticEffectID);

	if (Target == ETargetEnum::TE_None)
	{
		return;
	}

	Interhaptics::HapticBodyMapping::CommandData* returnTarget = (Interhaptics::HapticBodyMapping::CommandData*)malloc(sizeof(Interhaptics::HapticBodyMapping::CommandData));
	ConvertTarget(Target, returnTarget);

	InterhapticsEngine::AddTargetToEventMarshal(hapticEffectID, returnTarget, 1);
}

void AHapticSource::ConvertTarget(ETargetEnum Target, Interhaptics::HapticBodyMapping::CommandData* returnTarget)
{
	Interhaptics::HapticBodyMapping::GroupID		_BODYPART	= Interhaptics::HapticBodyMapping::GroupID::Hand;
	Interhaptics::HapticBodyMapping::Operator		_PLUS		= Interhaptics::HapticBodyMapping::Operator::Plus;
	Interhaptics::HapticBodyMapping::LateralFlag	_LATERAL	= Interhaptics::HapticBodyMapping::LateralFlag::Global;

	switch (Target)
	{
	case ETargetEnum::TE_LeftHand:
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
		break;
	case ETargetEnum::TE_RightHand:
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
		break;
	default:
		break;
	}

	*returnTarget = Interhaptics::HapticBodyMapping::CommandData(_PLUS, _BODYPART, _LATERAL);
}