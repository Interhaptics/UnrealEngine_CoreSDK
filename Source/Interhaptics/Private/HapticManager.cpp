/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "HapticManager.h"
#include "HAR.h"
#include "HapticDeviceManager.h"


AHapticManager* AHapticManager::CurrentInstance = nullptr;
FTimerHandle UpdateTimerHandle;

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
  // Set up timer to run at 30 Hz (1/30 seconds interval)
  const float UpdateInterval = 1.0f / 30.0f;
  GetWorldTimerManager().SetTimer(UpdateTimerHandle, this, &AHapticManager::UpdateHaptics, UpdateInterval, true);
}

void AHapticManager::UpdateHaptics()
{
  if (!InterhapticsEngine::HapticDeviceManager::IH_DEVICE_PROVIDERS.empty())  // Check if there are any devices
  {
    InterhapticsEngine::ComputeAllEvents((double)(GetWorld()->GetTimeSeconds()));
    InterhapticsEngine::HapticDeviceManager::RenderAll();
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("No Haptic Device found. Haptics will not be rendered."));
  }
}

void AHapticManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  Super::EndPlay(EndPlayReason);
  GetWorldTimerManager().ClearTimer(UpdateTimerHandle);
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
  FWorldContext* world = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);

  return world->World();
}

float AHapticManager::GetGlobalHapticIntensity()
{
  float intensity = static_cast<float>(InterhapticsEngine::GetGlobalIntensity());
  return intensity;
}

void AHapticManager::SetGlobalHapticIntensity(float Intensity)
{
	InterhapticsEngine::SetGlobalIntensity(static_cast<double>(Intensity));
}
