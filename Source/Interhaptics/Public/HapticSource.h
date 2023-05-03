/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#pragma once

#include "../../HapticEffect/Public/HapticEffect.h"
#include "../Public/HAR.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HapticSource.generated.h"


UENUM(BlueprintType)        //"BlueprintType" is essential to include
enum class ETargetEnum : uint8
{
	TE_LeftHand		UMETA(DisplayName = "Left hand"),
	TE_RightHand    UMETA(DisplayName = "Right hand"),
	TE_BothHand		UMETA(DisplayName = "Both hand"),
	TE_None			UMETA(DisplayName = "None")
};


UCLASS()
class INTERHAPTICS_API AHapticSource : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, Category = "Interhaptics")
		UHapticEffect* HapticEffect;
	UPROPERTY(EditAnywhere, Category = "Interhaptics")
		float VibrationOffset;
	UPROPERTY(EditAnywhere, Category = "Interhaptics")
		float TextureOffset;
	UPROPERTY(EditAnywhere, Category = "Interhaptics")
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
