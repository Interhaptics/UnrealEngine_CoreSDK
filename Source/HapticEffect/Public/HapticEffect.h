/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#pragma once

#include "Internationalization/Text.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"

#include "HapticEffect.generated.h"


UCLASS(BlueprintType, hidecategories=(Object))
class HAPTICEFFECT_API UHapticEffect
	: public UObject
{
	GENERATED_BODY()

public:

	/** Holds the stored text. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="HapticEffect")
	FText Text;
};
