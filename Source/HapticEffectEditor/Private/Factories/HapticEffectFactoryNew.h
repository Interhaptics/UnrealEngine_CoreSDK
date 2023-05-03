/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#pragma once

#include "Factories/Factory.h"
#include "UObject/ObjectMacros.h"

#include "HapticEffectFactoryNew.generated.h"


UCLASS(hidecategories=Object)
class UHapticEffectFactoryNew
	: public UFactory
{
	GENERATED_UCLASS_BODY()

public:

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override;
};
