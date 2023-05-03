/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#pragma once

#include "Factories/Factory.h"
#include "UObject/ObjectMacros.h"

#include "HapticEffectFactory.generated.h"


/**
 * Implements a factory for UTextAsset objects.
 */
UCLASS(hidecategories=Object)
class UHapticEffectFactory
	: public UFactory
{
	GENERATED_UCLASS_BODY()

public:


	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
};
