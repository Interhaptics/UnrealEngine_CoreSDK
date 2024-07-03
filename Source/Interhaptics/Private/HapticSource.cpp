/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
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
	InterhapticsEngine::PlayEvent(hapticEffectID, (double)(-VibrationOffset - GetWorld()->GetTimeSeconds()), 0.0, 0.0);
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

  Interhaptics::HapticBodyMapping::CommandData returnTarget = ConvertTarget(Target);
  InterhapticsEngine::AddTargetToEventMarshal(hapticEffectID, &returnTarget, 1);

}

Interhaptics::HapticBodyMapping::CommandData AHapticSource::ConvertTarget(ETargetEnum Target)
{
	Interhaptics::HapticBodyMapping::GroupID		_BODYPART	= Interhaptics::HapticBodyMapping::GroupID::Palm;
	Interhaptics::HapticBodyMapping::Operator		_PLUS		= Interhaptics::HapticBodyMapping::Operator::Plus;
	Interhaptics::HapticBodyMapping::LateralFlag	_LATERAL	= Interhaptics::HapticBodyMapping::LateralFlag::Global;

	switch (Target)
	{
	case ETargetEnum::TE_LeftPalm:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Palm;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
		break;
	case ETargetEnum::TE_RightPalm:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Palm;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
		break;
	case ETargetEnum::TE_BothPalms:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Palm;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
		break;
	case ETargetEnum::TE_LeftHand:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Hand;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
		break;
	case ETargetEnum::TE_RightHand:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Hand;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
		break;
	case ETargetEnum::TE_BothHands:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Hand;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
		break;
	case ETargetEnum::TE_LeftTrigger:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Index;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
		break;
	case ETargetEnum::TE_RightTrigger:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Index;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
		break;
	case ETargetEnum::TE_BothTriggers:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Index;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
		break;
  case ETargetEnum::TE_LeftHead:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Skull;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case ETargetEnum::TE_RightHead:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Skull;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case ETargetEnum::TE_Head:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Skull;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  case ETargetEnum::TE_LeftWaist:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Waist;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case ETargetEnum::TE_RightWaist:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Waist;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case ETargetEnum::TE_Waist:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Waist;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  case ETargetEnum::TE_LeftChest:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Chest;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case ETargetEnum::TE_RightChest:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Chest;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case ETargetEnum::TE_Chest:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Chest;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  case ETargetEnum::TE_LeftLeg:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Leg;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case ETargetEnum::TE_RightLeg:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Leg;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case ETargetEnum::TE_BothLegs:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Leg;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
    case ETargetEnum::TE_All:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::All;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
	default:
		break;
	}

  return Interhaptics::HapticBodyMapping::CommandData(_PLUS, _BODYPART, _LATERAL);
}

void AHapticSource::SetHapticEventIntensity(float Intensity)
{
	// Check if the haptic effect ID is valid and the intensity is within range
	if (hapticEffectID != -1)
	{
		InterhapticsEngine::SetEventIntensity(hapticEffectID, static_cast<double>(Intensity));
	}
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("AHapticSource::SetHapticEventIntensity: HapticEffectID is invalid. Effect will not be played."));
  }
}

AHapticSource* AHapticSource::CreateAndPlayHapticSource(UObject* WorldContextObject, UHapticEffect* Effect, ETargetEnum Target, float VibrationOffset)
{
  if (!WorldContextObject || !Effect) return nullptr; // Ensure both context and effect are valid
  UWorld* World = WorldContextObject->GetWorld();
  if (!World) return nullptr;

  // Spawn the HapticSource actor with a specific spawn parameters structure to defer its initialization
  FActorSpawnParameters SpawnParams;
  SpawnParams.bDeferConstruction = true; // This defers the PostInitializeComponents and other initializations
  AHapticSource* HapticSource = World->SpawnActor<AHapticSource>(AHapticSource::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
  if (!HapticSource) return nullptr;

  // Assign the haptic effect and properties
  HapticSource->HapticEffect = Effect;
  HapticSource->VibrationOffset = VibrationOffset;

  // Manually finish the spawning process and force initialization to occur now, after setting properties
  FTransform ActorTransform; // Default transform, you can customize this if needed
  HapticSource->FinishSpawning(ActorTransform);

  // Now setup targets and play the haptic effect
  HapticSource->SetTargets(Target);
  HapticSource->Play();

  return HapticSource;
}
