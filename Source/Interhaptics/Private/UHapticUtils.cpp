/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "UHapticUtils.h"

void UUHapticUtils::ConvertTarget(EAPITargetEnum Target, Interhaptics::HapticBodyMapping::CommandData* returnTarget)
{
  Interhaptics::HapticBodyMapping::GroupID		_BODYPART = Interhaptics::HapticBodyMapping::GroupID::Palm;
  Interhaptics::HapticBodyMapping::Operator		_PLUS = Interhaptics::HapticBodyMapping::Operator::Plus;
  Interhaptics::HapticBodyMapping::LateralFlag	_LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;

  switch (Target)
  {
  case EAPITargetEnum::TE_LeftPalm:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Palm;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case EAPITargetEnum::TE_RightPalm:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Palm;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case EAPITargetEnum::TE_BothPalms:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Palm;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  case EAPITargetEnum::TE_LeftHand:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Hand;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case EAPITargetEnum::TE_RightHand:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Hand;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case EAPITargetEnum::TE_BothHands:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Hand;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  case EAPITargetEnum::TE_LeftTrigger:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Index;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case EAPITargetEnum::TE_RightTrigger:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Index;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case EAPITargetEnum::TE_BothTriggers:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Index;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  case EAPITargetEnum::TE_LeftHead:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Skull;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case EAPITargetEnum::TE_RightHead:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Skull;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case EAPITargetEnum::TE_Head:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Skull;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
    case EAPITargetEnum::TE_LeftWaist:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Waist;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case EAPITargetEnum::TE_RightWaist:
  _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Waist;
  _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
  break;
  case EAPITargetEnum::TE_Waist:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Waist;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  case EAPITargetEnum::TE_LeftChest:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Chest;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case EAPITargetEnum::TE_RightChest:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Chest;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case EAPITargetEnum::TE_Chest:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Chest;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  case EAPITargetEnum::TE_LeftLeg:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Leg;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Left;
    break;
  case EAPITargetEnum::TE_RightLeg:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Leg;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Right;
    break;
  case EAPITargetEnum::TE_BothLegs:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::Leg;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  case EAPITargetEnum::TE_All:
    _BODYPART = Interhaptics::HapticBodyMapping::GroupID::All;
    _LATERAL = Interhaptics::HapticBodyMapping::LateralFlag::Global;
    break;
  default:
    break;
  }

  *returnTarget = Interhaptics::HapticBodyMapping::CommandData(_PLUS, _BODYPART, _LATERAL);
}

void UUHapticUtils::PlayHapticEffect(UHapticEffect* HapticEffect, EAPITargetEnum Target, float VibrationOffset)
{
  // Get the world using the static method on AHapticManager
  UWorld* World = AHapticManager::GetWorldStatic();
  if (!World)
  {
    UE_LOG(LogTemp, Warning, TEXT("Invalid world context."));
    return; // Early exit if world context is not available
  }
  if (HapticEffect == NULL)
  {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HAPS NOT ASSIGNED")));
    UE_LOG(LogTemp, Warning, TEXT("HAPS NOT ASSIGNED"));
    return;
  }

  int hapticEffectID = InterhapticsEngine::AddHM(TCHAR_TO_ANSI(*(HapticEffect->Text.ToString())));
  UE_LOG(LogTemp, Warning, TEXT("Haptic Effect ID: %d"), hapticEffectID);
  if (hapticEffectID == -1)
  {
    return;
  }

  InterhapticsEngine::RemoveAllTargetsFromEvent(hapticEffectID);

  if (Target == EAPITargetEnum::TE_None)
  {
    return;
  }
  UE_LOG(LogTemp, Warning, TEXT("Target: %d"), Target);
  Interhaptics::HapticBodyMapping::CommandData* returnTarget = (Interhaptics::HapticBodyMapping::CommandData*)malloc(sizeof(Interhaptics::HapticBodyMapping::CommandData));
  ConvertTarget(Target, returnTarget);
  UE_LOG(LogTemp, Warning, TEXT("Return Target: %d"), returnTarget);
  InterhapticsEngine::AddTargetToEventMarshal(hapticEffectID, returnTarget, 1);
  double playTime = (double)(-VibrationOffset - World->GetTimeSeconds());
  InterhapticsEngine::PlayEvent(hapticEffectID, playTime, 0.0, 0.0);
}

void UUHapticUtils::PlayParametricHapticEffect(const TArray<double>& Amplitude, const TArray<double>& Pitch, const TArray<double>& Transient, float FrequencyMin, float FrequencyMax, EAPITargetEnum Target, float VibrationOffset)
{
  UWorld* World = AHapticManager::GetWorldStatic();
  if (!World)
  {
    UE_LOG(LogTemp, Warning, TEXT("Invalid world context."));
    return; // Early exit if world context is not available
  }

  AHapticManager* HapticManager = AHapticManager::CurrentInstance; // Directly accessing the static instance
  if (!HapticManager)
  {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Haptic Manager not available"));
    return; // Early exit if Haptic Manager is not available
  }

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

  int hapticEffectID = InterhapticsEngine::AddParametricEffect(
    NonConstAmplitude.Num() > 0 ? NonConstAmplitude.GetData() : nullptr, NonConstAmplitude.Num(),
    NonConstPitch.Num() > 0 ? NonConstPitch.GetData() : nullptr, NonConstPitch.Num(),
    FrequencyMin, FrequencyMax,
    NonConstTransient.Num() > 0 ? NonConstTransient.GetData() : nullptr, NonConstTransient.Num(),
    false);
  UE_LOG(LogTemp, Log, TEXT("Playing Parametric Haptic Effect ID: %d"), hapticEffectID);
  if (hapticEffectID == -1)
  {
    return;
    UE_LOG(LogTemp, Warning, TEXT("Failed to create parametric haptic effect."));
  }

  Interhaptics::HapticBodyMapping::CommandData* returnTarget = (Interhaptics::HapticBodyMapping::CommandData*)malloc(sizeof(Interhaptics::HapticBodyMapping::CommandData));
  ConvertTarget(Target, returnTarget); 
  InterhapticsEngine::AddTargetToEventMarshal(hapticEffectID, returnTarget, 1);

  double playTime = (double)(- VibrationOffset - World->GetTimeSeconds());
  InterhapticsEngine::PlayEvent(hapticEffectID, playTime, 0.0, 0.0);

  free(returnTarget); // to free the dynamically allocated memory
}
