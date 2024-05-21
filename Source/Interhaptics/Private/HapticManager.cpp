/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "HapticManager.h"
#include "HAR.h"
#include "HapticDeviceManager.h"


AHapticManager* AHapticManager::CurrentInstance = nullptr;

// Sets default values
AHapticManager::AHapticManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  // Ensure that only one instance is set, or manage multiple instances intelligently
  if (!CurrentInstance)
    {
    CurrentInstance = this;
    UE_LOG(LogTemp, Log, TEXT("HapticManager instance created."));
    }
  else
    {
      UE_LOG(LogTemp, Warning, TEXT("Attempt to create multiple instances of HapticManager."));
      Destroy(); // Optionally destroy this newly attempted instance or handle as necessary
    }
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
  if (!InterhapticsEngine::HapticDeviceManager::IH_DEVICE_PROVIDERS.empty()) // Check if there are any devices
  {
    InterhapticsEngine::ComputeAllEvents((double)(GetWorld()->GetTimeSeconds()));
    try {
      InterhapticsEngine::HapticDeviceManager::RenderAll();
    }
    catch (const std::exception& e) {
      UE_LOG(LogTemp, Error, TEXT("Exception caught in Tick: %s"), *FString(e.what()));
    }
    catch (...) {
      UE_LOG(LogTemp, Error, TEXT("Unknown exception caught in Tick"));
    }
  }

}

void AHapticManager::BeginDestroy()
{
	InterhapticsEngine::HapticDeviceManager::CleanAll();
	InterhapticsEngine::Quit();

	Super::BeginDestroy();
}

// Destructor to clear the current instance if this was it
AHapticManager::~AHapticManager()
{
  if (CurrentInstance == this)
  {
    CurrentInstance = nullptr; // Clear the instance on destruction
    UE_LOG(LogTemp, Log, TEXT("HapticManager instance destroyed."));
  }
}

UWorld* AHapticManager::GetWorldStatic()
{
  return CurrentInstance ? CurrentInstance->GetWorld() : nullptr;
}

float AHapticManager::GetGlobalHapticIntensity()
{
	double intensity = InterhapticsEngine::GetGlobalIntensity();
	return static_cast<float>(intensity);
}

void AHapticManager::SetGlobalHapticIntensity(float Intensity)
{
	InterhapticsEngine::SetGlobalIntensity(static_cast<double>(Intensity));
}
