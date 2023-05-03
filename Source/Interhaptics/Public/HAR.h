/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
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
	INTERHAPTICS_API int GetOutputBufferSize(Interhaptics::HapticBodyMapping::Perception _perception, Interhaptics::HapticBodyMapping::BodyPartID _bodyPartID, int _x, int _y, int _z, Interhaptics::HapticBodyMapping::BufferDataType _dataType);
	INTERHAPTICS_API void GetOutputBuffer(double* _outputBuffer, int _bufferSize, Interhaptics::HapticBodyMapping::Perception _perception, Interhaptics::HapticBodyMapping::BodyPartID _bodyPartID, int _x, int _y, int _z, Interhaptics::HapticBodyMapping::BufferDataType _dataType);
	INTERHAPTICS_API void AddBodyPart(Interhaptics::HapticBodyMapping::Perception _perception, Interhaptics::HapticBodyMapping::BodyPartID _bodyPartID, int _xDimension, int _yDimension, int _zDimension, double _sampleRate, bool _hd, bool _splitFrequency, bool _splitTransient, bool _realTime);
	INTERHAPTICS_API void PlayEvent(int _hMaterialID, double _vibrationOffset = 0.0, double _textureOffset = 0.0, double _stiffnessOffset = 0.0);
	INTERHAPTICS_API void StopEvent(int _hMaterialID);
	INTERHAPTICS_API void ComputeAllEvents(double _curTime);
	INTERHAPTICS_API void RemoveTargetFromEvent(int _hMaterialID, std::vector<Interhaptics::HapticBodyMapping::CommandData> _target);
	INTERHAPTICS_API void AddTargetToEvent(int _hMaterialID, std::vector<Interhaptics::HapticBodyMapping::CommandData> _target);
	INTERHAPTICS_API void AddTargetToEventMarshal(int _hMaterialID, Interhaptics::HapticBodyMapping::CommandData* _target, int _size);
	INTERHAPTICS_API void RemoveAllTargetsFromEvent(int _hMaterialID);

	static void* v_Handle;
}

#endif
