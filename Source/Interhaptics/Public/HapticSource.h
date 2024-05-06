/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#pragma once

#include "../../HapticEffect/Public/HapticEffect.h"
#include "../Public/HAR.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Engine/World.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interhaptics")
		float TextureOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interhaptics")
		float StiffnessOffset;

	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
		int GetID();
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
		void Play();
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
		void Stop();
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
		void SetTargets(ETargetEnum Target);

	// Sets default values for this actor's properties
	AHapticSource();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

private:	
	int hapticEffectID = -1;

	void ConvertTarget(ETargetEnum Target, Interhaptics::HapticBodyMapping::CommandData* returnTarget);
};
