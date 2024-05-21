/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
* ​
*/

#pragma once

#include "../../HapticEffect/Public/HapticEffect.h"
#include "HAR.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "HapticSource.generated.h"


UENUM(BlueprintType)        //"BlueprintType" is essential to include
enum class ETargetEnum : uint8
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
class INTERHAPTICS_API AHapticSource : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interhaptics")
		UHapticEffect* HapticEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interhaptics")
		float VibrationOffset;

	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
		int GetID();
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
		void Play();
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
		void Stop();
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
		void SetTargets(ETargetEnum Target = ETargetEnum::TE_BothPalms);

	// Sets default values for this actor's properties
	AHapticSource();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Blueprint callable function to set the intensity for this haptic source
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
	void SetHapticEventIntensity(float Intensity);

  // Blueprint callable static function to instantiate and play a haptic effect
  UFUNCTION(BlueprintCallable, Category = "Interhaptics", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "2"))
  static AHapticSource* CreateAndPlayHapticSource(UObject* WorldContextObject, UHapticEffect* Effect, ETargetEnum Target = ETargetEnum::TE_BothPalms, float Vibration = 0.0f);

private:	
	int hapticEffectID = -1;

	void ConvertTarget(ETargetEnum Target, Interhaptics::HapticBodyMapping::CommandData* returnTarget);
};
