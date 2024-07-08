/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "HAR.h"
#include "enums.h"

#include "CoreMinimal.h"
#include <Core.h>


bool InterhapticsEngine::Init()
{
	bool ret = false;
	uintptr_t DllExport;
	DllExport = IH_GETDLLEXPORT("Init", DllExport, v_Handle);

	if (DllExport)
	{
		//Declare a type definition for the function
		typedef bool(*GetInit)();

		//Type cast the valid dll export to GetSum type
		GetInit InitFunc = (GetInit)(DllExport);

		//Call the function return the result
		ret = (bool)InitFunc();
	}

	return ret;
}

void InterhapticsEngine::Quit()
{
	uintptr_t DllExport;
	DllExport = IH_GETDLLEXPORT("Quit", DllExport, v_Handle);
	if (DllExport)
	{
		typedef void(*GetQuit)();
		GetQuit QuitFunc = (GetQuit)(DllExport);
		return (void)QuitFunc();
	}
}

int InterhapticsEngine::AddHM(const char* _content)
{
	uintptr_t DllExport;
	DllExport = IH_GETDLLEXPORT("AddHM", DllExport, v_Handle);
	if (DllExport)
	{
		typedef int(*GetAddHM)(const char* content);
		GetAddHM AddHMFunc = (GetAddHM)(DllExport);
		return (int)AddHMFunc(_content);
	}
	return -1;
}

int InterhapticsEngine::AddParametricEffect(float* _amplitude, int _amplitudeSize, float* _pitch, int _pitchSize, float _freqMin, float _freqMax, float* _transient, int _transientSize, bool _isLooping)
{
  uintptr_t DllExport = IH_GETDLLEXPORT("AddParametricEffect", DllExport, v_Handle);
  if (DllExport)
  {
    // Define the function type with double parameters
    typedef int (*FuncType)(double*, int, double*, int, double, double, double*, int, bool);
    FuncType func = (FuncType)(DllExport);

    // Create temporary double arrays and variables
    std::vector<double> doubleAmplitude(_amplitudeSize);
    std::vector<double> doublePitch(_pitchSize);
    std::vector<double> doubleTransient(_transientSize);
    double doubleFreqMin = static_cast<double>(_freqMin);
    double doubleFreqMax = static_cast<double>(_freqMax);

    // Convert float arrays to double
    for (int i = 0; i < _amplitudeSize; ++i)
      doubleAmplitude[i] = static_cast<double>(_amplitude[i]);
    for (int i = 0; i < _pitchSize; ++i)
      doublePitch[i] = static_cast<double>(_pitch[i]);
    for (int i = 0; i < _transientSize; ++i)
      doubleTransient[i] = static_cast<double>(_transient[i]);

    // Call the function with double parameters
    return func(doubleAmplitude.data(), _amplitudeSize,
      doublePitch.data(), _pitchSize,
      doubleFreqMin, doubleFreqMax,
      doubleTransient.data(), _transientSize,
      _isLooping);
  }
  return -1;  // Return -1 if the function pointer was not found
}

void InterhapticsEngine::PlayEvent(int _hMaterialID, double _vibrationOffset, double _textureOffset, double _stiffnessOffset)
{
	uintptr_t DllExport;
	DllExport = IH_GETDLLEXPORT("PlayEvent", DllExport, v_Handle);
	if (DllExport)
	{
		typedef void(*GetPlayEvent)(int _hMaterialID, double _vibrationOffset, double _textureOffset, double _stiffnessOffset);
		GetPlayEvent PlayEventFunc = (GetPlayEvent)(DllExport);
		return (void)PlayEventFunc(_hMaterialID, _vibrationOffset, _textureOffset, _stiffnessOffset);
	}
}

void InterhapticsEngine::StopEvent(int _hMaterialID)
{
	uintptr_t DllExport;
	DllExport = IH_GETDLLEXPORT("StopEvent", DllExport, v_Handle);
	if (DllExport)
	{
		typedef void(*GetStopEvent)(int _hMaterialID);
		GetStopEvent StopEventFunc = (GetStopEvent)(DllExport);
		return (void)StopEventFunc(_hMaterialID);
	}
}

void InterhapticsEngine::StopAllEvents()
{
	uintptr_t DllExport;
	DllExport = IH_GETDLLEXPORT("StopAllEvents", DllExport, v_Handle);
	if (DllExport)
	{
		typedef void(*GetStopAllEvents)();
		GetStopAllEvents StopAllEventsFunc = (GetStopAllEvents)(DllExport);
		return (void)StopAllEventsFunc();
	}
}

void InterhapticsEngine::ComputeAllEvents(double _curTime)
{
	uintptr_t DllExport;
	DllExport = IH_GETDLLEXPORT("ComputeAllEvents", DllExport, v_Handle);
	if (DllExport)
	{
		typedef void(*GetComputeAllEvents)(double _curTime);
		GetComputeAllEvents ComputeAllEventsFunc = (GetComputeAllEvents)(DllExport);
		return (void)ComputeAllEventsFunc(_curTime);
	}
}

void InterhapticsEngine::AddTargetToEvent(int _hMaterialID, std::vector<Interhaptics::HapticBodyMapping::CommandData> _target)
{
	uintptr_t DllExport;
	DllExport = IH_GETDLLEXPORT("AddTargetToEvent", DllExport, v_Handle);
	if (DllExport)
	{
		typedef void(*GetAddTargetToEvent)(int _hMaterialID, std::vector<Interhaptics::HapticBodyMapping::CommandData> _target);
		GetAddTargetToEvent AddTargetToEventFunc = (GetAddTargetToEvent)(DllExport);
		(void)AddTargetToEventFunc(_hMaterialID, _target);
		return;
	}
}

void InterhapticsEngine::AddTargetToEventMarshal(int _hMaterialID, Interhaptics::HapticBodyMapping::CommandData* _target, int _size)
{
	uintptr_t DllExport;
	DllExport = IH_GETDLLEXPORT("AddTargetToEventMarshal", DllExport, v_Handle);
	if (DllExport)
	{
		typedef void(*GetAddTargetToEventMarshal)(int _hMaterialID, Interhaptics::HapticBodyMapping::CommandData* _target, int _size);
		GetAddTargetToEventMarshal AddTargetToEventMarshalFunc = (GetAddTargetToEventMarshal)(DllExport);
		(void)AddTargetToEventMarshalFunc(_hMaterialID, _target, _size);
		return;
	}
}

void InterhapticsEngine::RemoveTargetFromEvent(int _hMaterialID, std::vector<Interhaptics::HapticBodyMapping::CommandData> _target)
{
	uintptr_t DllExport;
	DllExport = IH_GETDLLEXPORT("RemoveTargetFromEvent", DllExport, v_Handle);
	if (DllExport)
	{
		typedef void(*GetRemoveTargetFromEvent)(int _hMaterialID, std::vector<Interhaptics::HapticBodyMapping::CommandData> _target);
		GetRemoveTargetFromEvent RemoveTargetFromEventFunc = (GetRemoveTargetFromEvent)(DllExport);
		return (void)RemoveTargetFromEventFunc(_hMaterialID, _target);
	}
}

void InterhapticsEngine::RemoveAllTargetsFromEvent(int _hMaterialID)
{
	uintptr_t DllExport;
	DllExport = IH_GETDLLEXPORT("RemoveAllTargetsFromEvent", DllExport, v_Handle);
	if (DllExport)
	{
		typedef void(*GetRemoveAllTargetsFromEvent)(int _hMaterialID);
		GetRemoveAllTargetsFromEvent RemoveAllTargetsFromEventFunc = (GetRemoveAllTargetsFromEvent)(DllExport);
		return (void)RemoveAllTargetsFromEventFunc(_hMaterialID);
	}
}

void InterhapticsEngine::AddBodyPart(Interhaptics::HapticBodyMapping::Perception _perception, Interhaptics::HapticBodyMapping::BodyPartID _bodyPartID, int _xDimension, int _yDimension, int _zDimension, double _sampleRate, bool _hd, bool _splitFrequency, bool _splitTransient, bool _realTime)
{
	uintptr_t DllExport;
	DllExport = IH_GETDLLEXPORT("AddBodyPart", DllExport, v_Handle);
	if (DllExport)
	{
		typedef void(*GetAddBodyPart)(Interhaptics::HapticBodyMapping::Perception _perception, Interhaptics::HapticBodyMapping::BodyPartID _bodyPartID, int _xDimension, int _yDimension, int _zDimension, double _sampleRate, bool _hd, bool _splitFrequency, bool _splitTransient, bool _realTime);
		GetAddBodyPart AddBodyPartFunc = (GetAddBodyPart)(DllExport);
		return (void)AddBodyPartFunc(_perception, _bodyPartID, _xDimension, _yDimension, _zDimension, _sampleRate, _hd, _splitFrequency, _splitTransient, _realTime);
	}
}

double InterhapticsEngine::GetGlobalIntensity()
{
	uintptr_t DllExport = IH_GETDLLEXPORT("GetGlobalIntensity", DllExport, v_Handle);
	if (DllExport)
	{
		typedef double(*FuncType)();
		FuncType func = (FuncType)(DllExport);
		return func();
	}
	return -1; // Indicate failure or not initialized
}

void InterhapticsEngine::SetGlobalIntensity(double _intensity)
{
	uintptr_t DllExport = IH_GETDLLEXPORT("SetGlobalIntensity", DllExport, v_Handle);
	if (DllExport)
	{
		typedef void(*FuncType)(double);
		FuncType func = (FuncType)(DllExport);
		func(_intensity);
	}
}

void InterhapticsEngine::SetEventIntensity(int _hMaterialID, double _intensity)
{
	uintptr_t DllExport = IH_GETDLLEXPORT("SetEventIntensity", DllExport, v_Handle);
	if (DllExport)
	{
		typedef void(*FuncType)(int, double);
		FuncType func = (FuncType)(DllExport);
		func(_hMaterialID, _intensity);
	}
}

int InterhapticsEngine::startTriggerEffect(int id, bool isLeft)
{
#if PLATFORM_PS5
	if (v_DualSenseHandle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_DualSenseHandle, *FString("startTriggerEffect"));
		if (DllExport)
		{
			typedef int(*GetstartTriggerEffect)(int handle, int id, bool isLeft);
			GetstartTriggerEffect GetstartTriggerEffectFunc = (GetstartTriggerEffect)(DllExport);
			return (int)GetstartTriggerEffectFunc(0, id, isLeft);
		}
	}
#endif
	return -1;
}
int InterhapticsEngine::stopTriggerEffect(bool isLeft)
{
#if PLATFORM_PS5
	if (v_DualSenseHandle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_DualSenseHandle, *FString("stopTriggerEffect"));
		if (DllExport)
		{
			typedef int(*GetstopTriggerEffect)(int handle, bool isLeft);
			GetstopTriggerEffect GetstopTriggerEffectFunc = (GetstopTriggerEffect)(DllExport);
			return (int)GetstopTriggerEffectFunc(0, isLeft);
		}
	}
#endif
	return -1;
}
