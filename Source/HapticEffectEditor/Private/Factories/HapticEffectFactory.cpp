/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "HapticEffectFactory.h"

#include "Containers/UnrealString.h"
#include "HapticEffect.h"
#include "Misc/FileHelper.h"


UHapticEffectFactory::UHapticEffectFactory( const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{
	Formats.Add(FString(TEXT("haps;")) + NSLOCTEXT("UHapticEffectFactory", "FormatHaps", "Text File").ToString());
	SupportedClass = UHapticEffect::StaticClass();
	bCreateNew = false;
	bEditorImport = true;
}


UObject* UHapticEffectFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UHapticEffect* HapticEffect = nullptr;
	FString TextString;

	if (FFileHelper::LoadFileToString(TextString, *Filename))
	{
		HapticEffect = NewObject<UHapticEffect>(InParent, InClass, InName, Flags);
		HapticEffect->Text = FText::FromString(TextString);
	}

	bOutOperationCanceled = false;

	return HapticEffect;
}
