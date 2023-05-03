/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "HapticEffectFactoryNew.h"
#include "HapticEffect.h"


UHapticEffectFactoryNew::UHapticEffectFactoryNew(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UHapticEffect::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}


UObject* UHapticEffectFactoryNew::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UHapticEffect>(InParent, InClass, InName, Flags);
}


bool UHapticEffectFactoryNew::ShouldShowInNewMenu() const
{
	return true;
}
