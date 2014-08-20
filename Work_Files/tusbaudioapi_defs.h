/************************************************************************
 *
 *  Module:       tusbaudioapi_defs.h
 *
 *  Description:
 *    API related defs
 *    This file conforms to C standard. It can be used by C and C++ code.
 *
 *    This file is Windows specific.
 *
 *  Runtime Env.: Win32
 *
 *  Author(s):   
 *    Udo Eberhardt,  Udo.Eberhardt@thesycon.de
 *                
 *  Companies:
 *    Thesycon GmbH
 *                
 ************************************************************************/

#ifndef __tusbaudioapi_defs_h__
#define __tusbaudioapi_defs_h__


// status return value
// for status codes, see tstatus_codes.h
typedef DWORD TUsbAudioStatus;

// handle type used by the DLL
typedef unsigned int TUsbAudioHandle;


#define TUSBAUDIO_DEVICE_ARRIVAL_MSG		0x0001
#define TUSBAUDIO_DEVICE_REMOVED_MSG		0x0002


//
// State of DFU procedure
// Note: This does not correspond to the DFU states as defined in the DFU spec.
//
typedef enum tagTUsbAudioDfuProcState 
{
	DfuProcState_Idle = 0,
	DfuProcState_Initializing,
	DfuProcState_EnteringDfuMode,
	DfuProcState_InProgress,
	DfuProcState_EnteringAppMode,
	DfuProcState_Finished,
	DfuProcState_Failed

} TUsbAudioDfuProcState;

// flags
#define TUSBAUDIO_FLAG_UPLOADED_IMAGE						0x00000001
#define TUSBAUDIO_FLAG_NO_REBOOT								0x00000010
#define TUSBAUDIO_FLAG_ENUM_AFTER_REBOOT				0x00000020


//
// Indicates the firmware that is currently running on the device
//
typedef enum tagTUsbAudioDeviceRunMode 
{
	DeviceRunMode_APP = 0,	// application (audio) mode
	DeviceRunMode_DFU       // device firmware upgrade mode, no audio supported

} TUsbAudioDeviceRunMode;




#endif  // __tusbaudioapi_defs_h__

/*************************** EOF **************************************/
