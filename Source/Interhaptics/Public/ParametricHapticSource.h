/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
* ​
*/

#pragma once

#include "HAR.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Engine/World.h"
#include "ParametricHapticSource.generated.h"


UENUM(BlueprintType)        //"BlueprintType" is essential to include
enum class EParametricTargetEnum : uint8
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
class INTERHAPTICS_API AParametricHapticSource : public AActor
{
    GENERATED_BODY()

public:

	// Properties that can be set in the editor or Blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interhaptics|ParametricInput")
	TArray<double> Amplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interhaptics|ParametricInput")
	TArray<double> Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interhaptics|ParametricInput")
	float FrequencyMin;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interhaptics|ParametricInput")
	float FrequencyMax;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interhaptics|ParametricInput")
	TArray<double> Transient;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interhaptics")
	float VibrationOffset;

    // Blueprint callable function to play a haptic effect based on parametric input
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
	void PlayParametricEffect();
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
	int GetID();
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
	void Stop();
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
	void SetTargets(EParametricTargetEnum Target = EParametricTargetEnum::TE_BothPalms);
	// Blueprint callable function to set the intensity for this haptic source
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
	void SetHapticEventIntensity(float Intensity);
  // Blueprint callable static function to create, configure, and play a parametric haptic source
  UFUNCTION(BlueprintCallable, Category = "Interhaptics", meta = (WorldContext = "WorldContextObject", DisplayName = "Create and Play Parametric Haptics"))
  static AParametricHapticSource* CreateAndPlayParametricHaptics(
    UObject* WorldContextObject,
    const TArray<double>& InAmplitude,
    const TArray<double>& InPitch,
    const TArray<double>& InTransient,
    float InFrequencyMin = 65.0f,
    float InFrequencyMax = 300.0f,
    EParametricTargetEnum Target = EParametricTargetEnum::TE_BothPalms,
    float InVibrationOffset = 0.0f);

	// Sets default values for this actor's properties
	AParametricHapticSource();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

private:
	int hapticEffectID = -1;

  Interhaptics::HapticBodyMapping::CommandData ConvertTarget(EParametricTargetEnum Target);
	// Helper function to log array contents for debugging
	void LogArrayContents(const TArray<double>& Array, const TCHAR* ArrayName);
};
