/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
* ​
*/

#pragma once

#include "../../HapticEffect/Public/HapticEffect.h"
#include "HAR.h"
#include "HapticManager.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UHapticUtils.generated.h"


UENUM(BlueprintType)
enum class EAPITargetEnum : uint8
{
  TE_LeftPalm      UMETA(DisplayName = "Left Palm"),
  TE_RightPalm     UMETA(DisplayName = "Right Palm"),
  TE_BothPalms     UMETA(DisplayName = "Both Palms"),
  TE_LeftHand      UMETA(DisplayName = "Left Hand"),
  TE_RightHand     UMETA(DisplayName = "Right Hand"),
  TE_BothHands      UMETA(DisplayName = "Both Hands"),
  TE_LeftTrigger   UMETA(DisplayName = "Left Trigger"),
  TE_RightTrigger  UMETA(DisplayName = "Right Trigger"),
  TE_BothTriggers  UMETA(DisplayName = "Both Triggers"),
  TE_LeftHead      UMETA(DisplayName = "Left Head"),
  TE_RightHead     UMETA(DisplayName = "Right Head"),
  TE_Head          UMETA(DisplayName = "Head"),
  TE_LeftWaist     UMETA(DisplayName = "Left Waist"),
  TE_RightWaist    UMETA(DisplayName = "Right Waist"),
  TE_Waist         UMETA(DisplayName = "Entire Waist"),
  TE_LeftChest     UMETA(DisplayName = "Left Chest"),
  TE_RightChest    UMETA(DisplayName = "Right Chest"),
  TE_Chest         UMETA(DisplayName = "Entire Chest"),
  TE_LeftLeg       UMETA(DisplayName = "Left Leg"),
  TE_RightLeg      UMETA(DisplayName = "Right Leg"),
  TE_BothLegs      UMETA(DisplayName = "Both Legs"),
  TE_All           UMETA(DisplayName = "All"),
  TE_None          UMETA(DisplayName = "None")
};

UCLASS()
class INTERHAPTICS_API UUHapticUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable, Category = "Interhaptics")
  static void PlayHapticEffect(UHapticEffect* HapticEffect, EAPITargetEnum Target = EAPITargetEnum::TE_BothPalms, float VibrationOffsetAPI = 0.0f);

  UFUNCTION(BlueprintCallable, Category = "Interhaptics")
  static void PlayParametricHapticEffect(const TArray<float>& Amplitude, const TArray<float>& Pitch, const TArray<float>& Transient, float FrequencyMin = 65.0f, float FrequencyMax = 300.0f, EAPITargetEnum Target = EAPITargetEnum::TE_BothPalms, float VibrationOffsetAPI = 0.0f);

private:
  int hapticEffectID = -1;

  static Interhaptics::HapticBodyMapping::CommandData ConvertTarget(EAPITargetEnum Target);
};
