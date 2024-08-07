/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
* ​
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "HapticManager.generated.h"

UCLASS()
class INTERHAPTICS_API AHapticManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHapticManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  void UpdateHaptics();

  void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called right before BeginPlay
	virtual void PreInitializeComponents() override;
	// Called when actor is destroyed
	virtual void BeginDestroy() override;
  static AHapticManager* CurrentInstance;

  virtual ~AHapticManager();

  static UWorld* GetWorldStatic();

	// Blueprint callable function to get the global intensity
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
	float GetGlobalHapticIntensity();

	// Blueprint callable function to set the global intensity
	UFUNCTION(BlueprintCallable, Category = "Interhaptics")
	void SetGlobalHapticIntensity(float Intensity);
};
