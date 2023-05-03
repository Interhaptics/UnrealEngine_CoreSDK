/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "HapticManager.h"
#include "HAR.h"
#include "HapticDeviceManager.h"

// Sets default values
AHapticManager::AHapticManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHapticManager::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	InterhapticsEngine::Init();
	InterhapticsEngine::HapticDeviceManager::InitializeAll();
}

// Called when the game starts or when spawned
void AHapticManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHapticManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InterhapticsEngine::ComputeAllEvents((double)(GetWorld()->GetTimeSeconds()));
	InterhapticsEngine::HapticDeviceManager::RenderAll();
}

void AHapticManager::BeginDestroy()
{
	InterhapticsEngine::HapticDeviceManager::CleanAll();
	InterhapticsEngine::Quit();

	Super::BeginDestroy();
}