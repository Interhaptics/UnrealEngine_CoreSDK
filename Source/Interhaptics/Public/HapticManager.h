/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#pragma once

#include "CoreMinimal.h"
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

public:
	// Called right before BeginPlay
	virtual void PreInitializeComponents() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when actor is destroyed
	virtual void BeginDestroy() override;
};
