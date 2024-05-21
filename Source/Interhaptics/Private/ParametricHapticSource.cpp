/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "ParametricHapticSource.h"

int AParametricHapticSource::GetID()
{
	return hapticEffectID;
}

// Sets default values
AParametricHapticSource::AParametricHapticSource()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrequencyMin = 65.0;  // Set default frequency min
	FrequencyMax = 300.0;  // Set default frequency max
}

// Called when the game starts or when spawned
void AParametricHapticSource::PostInitializeComponents()
{
	Super::PostInitializeComponents();

  // Debug logs to check array content and size
  UE_LOG(LogTemp, Log, TEXT("Playing Parametric Effect:"));
  UE_LOG(LogTemp, Log, TEXT("Amplitude Array Size: %d"), Amplitude.Num());
  UE_LOG(LogTemp, Log, TEXT("Pitch Array Size: %d"), Pitch.Num());
  UE_LOG(LogTemp, Log, TEXT("Transient Array Size: %d"), Transient.Num());

  // Log each element in the Amplitude, Pitch, and Transient arrays
  LogArrayContents(Amplitude, TEXT("Amplitude"));
  LogArrayContents(Pitch, TEXT("Pitch"));
  LogArrayContents(Transient, TEXT("Transient"));

  // Ensure Amplitude and Pitch arrays are even in size
  int amplitudeSize = Amplitude.Num() % 2 == 0 ? Amplitude.Num() : Amplitude.Num() - 1;
  int pitchSize = Pitch.Num() % 2 == 0 ? Pitch.Num() : Pitch.Num() - 1;

  TArray<double> NonConstAmplitude(Amplitude.GetData(), amplitudeSize);
  TArray<double> NonConstPitch(Pitch.GetData(), pitchSize);

  if (Amplitude.Num() % 2 != 0) {
    UE_LOG(LogTemp, Warning, TEXT("Amplitude array truncated to ensure even size. New size: %d"), NonConstAmplitude.Num());
  }
  if (Pitch.Num() % 2 != 0) {
    UE_LOG(LogTemp, Warning, TEXT("Pitch array truncated to ensure even size. New size: %d"), NonConstPitch.Num());
  }

  // Ensure Transient array is a multiple of three
  int transientSize = (Transient.Num() / 3) * 3;
  TArray<double> NonConstTransient(Transient.GetData(), transientSize);

  if (Transient.Num() % 3 != 0) {
    UE_LOG(LogTemp, Warning, TEXT("Transient array truncated to multiple of three. New size: %d"), NonConstTransient.Num());
  }

  // Log all elements of the arrays for debug purposes
  FString amplitudeValues, pitchValues, transientValues;
  for (int i = 0; i < NonConstAmplitude.Num(); i++) {
    amplitudeValues += FString::Printf(TEXT("%f, "), NonConstAmplitude[i]);
  }
  for (int i = 0; i < NonConstPitch.Num(); i++) {
    pitchValues += FString::Printf(TEXT("%f, "), NonConstPitch[i]);
  }
  for (int i = 0; i < NonConstTransient.Num(); i++) {
    transientValues += FString::Printf(TEXT("%f, "), NonConstTransient[i]);
  }

  UE_LOG(LogTemp, Log, TEXT("Amplitude values: %s"), *amplitudeValues);
  UE_LOG(LogTemp, Log, TEXT("Pitch values: %s"), *pitchValues);
  UE_LOG(LogTemp, Log, TEXT("Transient values: %s"), *transientValues);

  // Call to the haptic engine with hardcoded values
   hapticEffectID = InterhapticsEngine::AddParametricEffect(
     NonConstAmplitude.Num() > 0 ? NonConstAmplitude.GetData() : nullptr, NonConstAmplitude.Num(),
     NonConstPitch.Num() > 0 ? NonConstPitch.GetData() : nullptr, NonConstPitch.Num(),
    FrequencyMin, FrequencyMax,
     NonConstTransient.Num() > 0 ? NonConstTransient.GetData() : nullptr, NonConstTransient.Num(),
    false);

  // Optionally log the ID of the created haptic effect
  UE_LOG(LogTemp, Log, TEXT("Created Haptic Effect ID: %d"), hapticEffectID);
}

// Called every frame
void AParametricHapticSource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParametricHapticSource::PlayParametricEffect()
{
	if (hapticEffectID == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create parametric haptic effect."));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Parametric haptic effect created successfully with ID: %d"), hapticEffectID);
		InterhapticsEngine::PlayEvent(hapticEffectID, (double)(-VibrationOffset - GetWorld()->GetTimeSeconds()), 0.0, 0.0);
	}
}

void AParametricHapticSource::Stop()
{
	InterhapticsEngine::StopEvent(hapticEffectID);
}

void AParametricHapticSource::SetTargets(EParametricTargetEnum Target)
{
	if (hapticEffectID == -1)
	{
		return;
	}

	InterhapticsEngine::RemoveAllTargetsFromEvent(hapticEffectID);

	if (Target == EParametricTargetEnum::TE_None)
	{
		return;
	}

	// Switch to new/delete for memory allocation in UE4
	Interhaptics::HapticBodyMapping::CommandData* returnTarget = (Interhaptics::HapticBodyMapping::CommandData*)malloc(sizeof(Interhaptics::HapticBodyMapping::CommandData));
	ConvertTarget(Target, returnTarget);
	InterhapticsEngine::AddTargetToEventMarshal(hapticEffectID, returnTarget, 1);
}

void AParametricHapticSource::ConvertTarget(EParametricTargetEnum Target, Interhaptics::HapticBodyMapping::CommandData* returnTarget)
{
	Interhaptics::HapticBodyMapping::GroupID		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Palm;
	Interhaptics::HapticBodyMapping::Operator		_PLUS = Interhaptics::HapticBodyMapping::Operator::Plus;
	Interhaptics::HapticBodyMapping::LateralFlag	_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;

	switch (Target)
	{
	case EParametricTargetEnum::TE_LeftPalm:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Palm;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
		break;
	case EParametricTargetEnum::TE_RightPalm:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Palm;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
		break;
	case EParametricTargetEnum::TE_BothPalms:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Palm;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
		break;
	case EParametricTargetEnum::TE_LeftHand:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Hand;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
		break;
	case EParametricTargetEnum::TE_RightHand:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Hand;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
		break;
	case EParametricTargetEnum::TE_BothHands:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Hand;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
		break;
	case EParametricTargetEnum::TE_LeftTrigger:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Index;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
		break;
	case EParametricTargetEnum::TE_RightTrigger:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Index;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
		break;
	case EParametricTargetEnum::TE_BothTriggers:
		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Index;
		_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
		break;
  case EParametricTargetEnum::TE_LeftHead:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Skull;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case EParametricTargetEnum::TE_RightHead:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Skull;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case EParametricTargetEnum::TE_Head:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Skull;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  case EParametricTargetEnum::TE_LeftWaist:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Waist;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case EParametricTargetEnum::TE_RightWaist:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Waist;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case EParametricTargetEnum::TE_Waist:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Waist;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  case EParametricTargetEnum::TE_LeftChest:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Chest;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case EParametricTargetEnum::TE_RightChest:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Chest;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case EParametricTargetEnum::TE_Chest:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Chest;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  case EParametricTargetEnum::TE_LeftLeg:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Leg;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case EParametricTargetEnum::TE_RightLeg:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Leg;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case EParametricTargetEnum::TE_BothLegs:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Leg;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  case EParametricTargetEnum::TE_All:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::All;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
	default:
		break;
	}

	*returnTarget = Interhaptics::HapticBodyMapping::CommandData(_PLUS, _BODYPART, _LATERAL);
}

void AParametricHapticSource::SetHapticEventIntensity(float Intensity)
{
	// Check if the haptic effect ID is valid and the intensity is within range
	if (hapticEffectID != -1 && Intensity >= 0)
	{
		InterhapticsEngine::SetEventIntensity(hapticEffectID, static_cast<double>(Intensity));
	}
}

AParametricHapticSource* AParametricHapticSource::CreateAndPlayParametricHaptics(
  UObject* WorldContextObject,
  const TArray<double>& InAmplitude,
  const TArray<double>& InPitch,
  const TArray<double>& InTransient,
  float InFrequencyMin,
  float InFrequencyMax,
  EParametricTargetEnum Target,
  float InVibrationOffset)
{
  if (!WorldContextObject) return nullptr;
  UWorld* World = WorldContextObject->GetWorld();
  if (!World) return nullptr;

  FActorSpawnParameters SpawnParams;
  SpawnParams.bDeferConstruction = true;
  AParametricHapticSource* ParametricHapticSource = World->SpawnActor<AParametricHapticSource>(AParametricHapticSource::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
  if (!ParametricHapticSource) return nullptr;

  ParametricHapticSource->Amplitude = InAmplitude;
  ParametricHapticSource->Pitch = InPitch;
  ParametricHapticSource->FrequencyMin = InFrequencyMin;
  ParametricHapticSource->FrequencyMax = InFrequencyMax;
  ParametricHapticSource->Transient = InTransient;
  ParametricHapticSource->VibrationOffset = InVibrationOffset;

  FTransform Transform; // Default transform
  ParametricHapticSource->FinishSpawning(Transform);

  ParametricHapticSource->SetTargets(Target);
  ParametricHapticSource->PlayParametricEffect();

  return ParametricHapticSource;
}

void AParametricHapticSource::LogArrayContents(const TArray<double>& Array, const TCHAR* ArrayName)
{
	FString ArrayContents;
	for (int i = 0; i < Array.Num(); ++i)
	{
		ArrayContents += FString::Printf(TEXT("%f, "), Array[i]);
	}
	UE_LOG(LogTemp, Log, TEXT("%s Array Contents: [%s]"), ArrayName, *ArrayContents);
}
