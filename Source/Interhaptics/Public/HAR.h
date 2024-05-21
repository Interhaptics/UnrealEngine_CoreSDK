/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
* ​
*/

#ifndef IH_HAR_H
#define IH_HAR_H

#include "enums.h"
#include <vector>

namespace InterhapticsEngine
{
	INTERHAPTICS_API bool Init();
	INTERHAPTICS_API void Quit();
	INTERHAPTICS_API int AddHM(const char* _content);
	INTERHAPTICS_API int AddParametricEffect(double* _amplitude, int _amplitudeSize, double* _pitch, int _pitchSize, double _freqMin, double _freqMax, double* _transient, int _transientSize, bool _isLooping);
	INTERHAPTICS_API void AddBodyPart(Interhaptics::HapticBodyMapping::Perception _perception, Interhaptics::HapticBodyMapping::BodyPartID _bodyPartID, int _xDimension, int _yDimension, int _zDimension, double _sampleRate, bool _hd, bool _splitFrequency, bool _splitTransient, bool _realTime);
	INTERHAPTICS_API void PlayEvent(int _hMaterialID, double _vibrationOffset = 0.0, double _textureOffset = 0.0, double _stiffnessOffset = 0.0);
	INTERHAPTICS_API void StopEvent(int _hMaterialID);
	INTERHAPTICS_API void StopAllEvents();
	INTERHAPTICS_API void ComputeAllEvents(double _curTime);
	INTERHAPTICS_API void RemoveTargetFromEvent(int _hMaterialID, std::vector<Interhaptics::HapticBodyMapping::CommandData> _target);
	INTERHAPTICS_API void AddTargetToEvent(int _hMaterialID, std::vector<Interhaptics::HapticBodyMapping::CommandData> _target);
	INTERHAPTICS_API void AddTargetToEventMarshal(int _hMaterialID, Interhaptics::HapticBodyMapping::CommandData* _target, int _size);
	INTERHAPTICS_API void RemoveAllTargetsFromEvent(int _hMaterialID);

	// Intensity control methods
	INTERHAPTICS_API double GetGlobalIntensity();
	INTERHAPTICS_API void SetGlobalIntensity(double _intensity);
	INTERHAPTICS_API void SetEventIntensity(int _hMaterialID, double _intensity);
	INTERHAPTICS_API int startTriggerEffect(int id, bool isLeft);
	INTERHAPTICS_API int stopTriggerEffect(bool isLeft);

	static void* v_Handle;

	#if PLATFORM_PS5
	static void* v_DualSenseHandle;
	#endif
}

#endif
