/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "..\Public\HAR.h"
#include "CoreMinimal.h"
#include <Core.h>

bool InterhapticsEngine::Init()
{
	bool ret = false;
	if (v_Handle) //We have a valid dll handle
	{
		//We will try to store the function that exists in our loaded dll file in the DllExport
		//void* DllExport = FPlatformProcess::GetDllExport(DllHandle,*FString("MyFunctionName"));
		void* DllExport = FPlatformProcess::GetDllExport(v_Handle, *FString("Init"));
		if (DllExport)
		{
			//Declare a type definition for the function
			typedef bool(*GetInit)();

			//Type cast the valid dll export to GetSum type
			GetInit InitFunc = (GetInit)(DllExport);

			//Call the function return the result
			ret = (bool)InitFunc();
		}
	}
	return ret;
}

void InterhapticsEngine::Quit()
{
	if (v_Handle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_Handle, *FString("Quit"));
		if (DllExport)
		{
			typedef void(*GetQuit)();
			GetQuit QuitFunc = (GetQuit)(DllExport);
			return (void)QuitFunc();
		}
	}
}

int InterhapticsEngine::AddHM(const char* _content)
{
	if (v_Handle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_Handle, *FString("AddHM"));
		if (DllExport)
		{
			typedef int(*GetAddHM)(const char* content);
			GetAddHM AddHMFunc = (GetAddHM)(DllExport);
			return (int)AddHMFunc(_content);
		}
	}
	return -1;
}

void InterhapticsEngine::PlayEvent(int _hMaterialID, double _vibrationOffset, double _textureOffset, double _stiffnessOffset)
{
	if (v_Handle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_Handle, *FString("PlayEvent"));
		if (DllExport)
		{
			typedef void(*GetPlayEvent)(int _hMaterialID, double _vibrationOffset, double _textureOffset, double _stiffnessOffset);
			GetPlayEvent PlayEventFunc = (GetPlayEvent)(DllExport);
			return (void)PlayEventFunc(_hMaterialID, _vibrationOffset, _textureOffset, _stiffnessOffset);
		}
	}
}

void InterhapticsEngine::StopEvent(int _hMaterialID)
{
	if (v_Handle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_Handle, *FString("StopEvent"));
		if (DllExport)
		{
			typedef void(*GetStopEvent)(int _hMaterialID);
			GetStopEvent StopEventFunc = (GetStopEvent)(DllExport);
			return (void)StopEventFunc(_hMaterialID);
		}
	}
}

void InterhapticsEngine::ComputeAllEvents(double _curTime)
{
	if (v_Handle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_Handle, *FString("ComputeAllEvents"));
		if (DllExport)
		{
			typedef void(*GetComputeAllEvents)(double _curTime);
			GetComputeAllEvents ComputeAllEventsFunc = (GetComputeAllEvents)(DllExport);
			return (void)ComputeAllEventsFunc(_curTime);
		}
	}
}

void InterhapticsEngine::AddTargetToEvent(int _hMaterialID, std::vector<Interhaptics::HapticBodyMapping::CommandData> _target)
{
	if (v_Handle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_Handle, *FString("AddTargetToEvent"));
		if (DllExport)
		{
			typedef void(*GetAddTargetToEvent)(int _hMaterialID, std::vector<Interhaptics::HapticBodyMapping::CommandData> _target);
			GetAddTargetToEvent AddTargetToEventFunc = (GetAddTargetToEvent)(DllExport);
			(void)AddTargetToEventFunc(_hMaterialID, _target);
			return;
		}
	}
}

void InterhapticsEngine::AddTargetToEventMarshal(int _hMaterialID, Interhaptics::HapticBodyMapping::CommandData* _target, int _size)
{
	if (v_Handle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_Handle, *FString("AddTargetToEventMarshal"));
		if (DllExport)
		{
			typedef void(*GetAddTargetToEventMarshal)(int _hMaterialID, Interhaptics::HapticBodyMapping::CommandData* _target, int _size);
			GetAddTargetToEventMarshal AddTargetToEventMarshalFunc = (GetAddTargetToEventMarshal)(DllExport);
			(void)AddTargetToEventMarshalFunc(_hMaterialID, _target, _size);
			return;
		}
	}
}

void InterhapticsEngine::RemoveTargetFromEvent(int _hMaterialID, std::vector<Interhaptics::HapticBodyMapping::CommandData> _target)
{
	if (v_Handle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_Handle, *FString("RemoveTargetFromEvent"));
		if (DllExport)
		{
			typedef void(*GetRemoveTargetFromEvent)(int _hMaterialID, std::vector<Interhaptics::HapticBodyMapping::CommandData> _target);
			GetRemoveTargetFromEvent RemoveTargetFromEventFunc = (GetRemoveTargetFromEvent)(DllExport);
			return (void)RemoveTargetFromEventFunc(_hMaterialID, _target);
		}
	}
}

void InterhapticsEngine::RemoveAllTargetsFromEvent(int _hMaterialID)
{
	if (v_Handle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_Handle, *FString("RemoveAllTargetsFromEvent"));
		if (DllExport)
		{
			typedef void(*GetRemoveAllTargetsFromEvent)(int _hMaterialID);
			GetRemoveAllTargetsFromEvent RemoveAllTargetsFromEventFunc = (GetRemoveAllTargetsFromEvent)(DllExport);
			return (void)RemoveAllTargetsFromEventFunc(_hMaterialID);
		}
	}
}

void InterhapticsEngine::AddBodyPart(Interhaptics::HapticBodyMapping::Perception _perception, Interhaptics::HapticBodyMapping::BodyPartID _bodyPartID, int _xDimension, int _yDimension, int _zDimension, double _sampleRate, bool _hd, bool _splitFrequency, bool _splitTransient, bool _realTime)
{
	if (v_Handle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_Handle, *FString("AddBodyPart"));
		if (DllExport)
		{
			typedef void(*GetAddBodyPart)(Interhaptics::HapticBodyMapping::Perception _perception, Interhaptics::HapticBodyMapping::BodyPartID _bodyPartID, int _xDimension, int _yDimension, int _zDimension, double _sampleRate, bool _hd, bool _splitFrequency, bool _splitTransient, bool _realTime);
			GetAddBodyPart AddBodyPartFunc = (GetAddBodyPart)(DllExport);
			return (void)AddBodyPartFunc(_perception, _bodyPartID, _xDimension, _yDimension, _zDimension, _sampleRate, _hd, _splitFrequency, _splitTransient, _realTime);
		}
	}
}

int InterhapticsEngine::GetOutputBufferSize(Interhaptics::HapticBodyMapping::Perception _perception, Interhaptics::HapticBodyMapping::BodyPartID _bodyPartID, int _x, int _y, int _z, Interhaptics::HapticBodyMapping::BufferDataType _dataType)
{
	if (v_Handle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_Handle, *FString("GetOutputBufferSize"));
		if (DllExport)
		{
			typedef int(*GetGetOutputBufferSize)(Interhaptics::HapticBodyMapping::Perception _perception, Interhaptics::HapticBodyMapping::BodyPartID _bodyPartID, int _x, int _y, int _z, Interhaptics::HapticBodyMapping::BufferDataType _dataType);
			GetGetOutputBufferSize GetOutputBufferSizeFunc = (GetGetOutputBufferSize)(DllExport);
			return (int)GetOutputBufferSizeFunc(_perception, _bodyPartID, _x, _y, _z, _dataType);
		}
	}

	return -1;
}

void InterhapticsEngine::GetOutputBuffer(double* _outputBuffer, int _bufferSize, Interhaptics::HapticBodyMapping::Perception _perception, Interhaptics::HapticBodyMapping::BodyPartID _bodyPartID, int _x, int _y, int _z, Interhaptics::HapticBodyMapping::BufferDataType _dataType)
{
	if (v_Handle)
	{
		void* DllExport = FPlatformProcess::GetDllExport(v_Handle, *FString("GetOutputBuffer"));
		if (DllExport)
		{
			typedef void(*GetGetOutputBuffer)(Interhaptics::HapticBodyMapping::Perception _perception, Interhaptics::HapticBodyMapping::BodyPartID _bodyPartID, int _x, int _y, int _z, Interhaptics::HapticBodyMapping::BufferDataType _dataType);
			GetGetOutputBuffer GetOutputBufferFunc = (GetGetOutputBuffer)(DllExport);
			return (void)GetOutputBufferFunc(_perception, _bodyPartID, _x, _y, _z, _dataType);
		}
	}
}
