/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "Containers/Array.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Templates/SharedPointer.h"

#define LOCTEXT_NAMESPACE "FHapticEffectEditorModule"


/**
 * Implements the TextAssetEditor module.
 */
class FHapticEffectEditorModule
	: public IModuleInterface
{
public:

	//~ IModuleInterface interface

	virtual bool SupportsDynamicReloading() override
	{
		return true;
	}

};


IMPLEMENT_MODULE(FHapticEffectEditorModule, HapticEffectEditor);


#undef LOCTEXT_NAMESPACE
