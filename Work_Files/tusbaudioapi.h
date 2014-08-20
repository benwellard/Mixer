/************************************************************************
 *
 *  Module:       tusbaudioapi.h
 *  Description:  Thesycon USB Audio Class Driver API DLL interface
 *
 *  Author(s):   
 *    Udo Eberhardt, Frank Senf
 *                
 *  Companies:
 *    Thesycon GmbH, Germany      http://www.thesycon.de
 *                
 ************************************************************************/

#ifndef __tusbaudioapi_h__
#define __tusbaudioapi_h__

//
// Version of the software interface exported by the DLL.
//
// If changes are made to the programming interface that are compatible with
// previous versions then the minor version number (low order byte) will
// be incremented.
// If changes are made that cause an incompatibility with previous versions
// of the interface then the major version number (high order byte) will be
// incremented.
//
#define TUSBAUDIO_API_VERSION_MJ   4
#define TUSBAUDIO_API_VERSION_MN   2

// version dword, high word = major version, low word = minor version
#define TUSBAUDIO_API_VERSION  \
  ( ((unsigned int)TUSBAUDIO_API_VERSION_MN)|(((unsigned int)TUSBAUDIO_API_VERSION_MJ)<<16) )



//
// Definitions, types, constants, etc.
//
#include "tstatus_codes.h"
#include "tusbaudio_defs.h"
#include "tusbaudioapi_defs.h"



// function decoration
#if defined(TUSBAUDIO_EXPORTS)
  // if .h file is included by the DLL implementation:
  #define TUSBAUDIO_DECL
#else
  // if .h file is included by a user's application
  #define TUSBAUDIO_DECL  __declspec(dllimport)
#endif

// calling convention
#define TUSBAUDIO_CALL  __stdcall



//
// Functions exported by the DLL
//

#if defined (__cplusplus)
extern "C" {
#endif


//
// Returns the TUSBAUDIO_API_VERSION constant the DLL has been compiled with.
//
TUSBAUDIO_DECL
unsigned int
TUSBAUDIO_CALL
TUSBAUDIO_GetApiVersion(void);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
unsigned int
TUSBAUDIO_CALL
F_TUSBAUDIO_GetApiVersion(void);


//
// Check the given version number against the version of the software interface (API)
// that is exported by the DLL. Returns 1 if the DLL is compatible.
//
TUSBAUDIO_DECL
int
TUSBAUDIO_CALL
TUSBAUDIO_CheckApiVersion(
  unsigned int majorVersion,
  unsigned int minorVersion
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
int
TUSBAUDIO_CALL
F_TUSBAUDIO_CheckApiVersion(
  unsigned int majorVersion,
  unsigned int minorVersion
  );



//
// Register for plug/unplug notifications.
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_RegisterPnpNotification(
  HANDLE deviceArrivalEvent,	// optional, can be NULL
  HANDLE deviceRemovedEvent,	// optional, can be NULL
  void* windowHandle,					// optional, can be NULL
	unsigned int windowMsgCode,
  unsigned int flags					// reserved for future use
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_RegisterPnpNotification(
  HANDLE deviceArrivalEvent,	// optional, can be NULL
  HANDLE deviceRemovedEvent,	// optional, can be NULL
  void* windowHandle,					// optional, can be NULL
	unsigned int windowMsgCode,
  unsigned int flags					// reserved for future use
	);

//
// Unregister for plug/unplug notifications.
//
TUSBAUDIO_DECL
void
TUSBAUDIO_CALL
TUSBAUDIO_UnregisterPnpNotification(void);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
void
TUSBAUDIO_CALL
F_TUSBAUDIO_UnregisterPnpNotification(void);




//
// scan for devices, build internal device list
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_EnumerateDevices(void);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_EnumerateDevices(void);


//
// query the number of devices available
//
TUSBAUDIO_DECL
unsigned int
TUSBAUDIO_CALL
TUSBAUDIO_GetDeviceCount(void);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
unsigned int
TUSBAUDIO_CALL
F_TUSBAUDIO_GetDeviceCount(void);


//
// open a USB audio device
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_OpenDeviceByIndex(
  unsigned int deviceIndex,
  TUsbAudioHandle* deviceHandle
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_OpenDeviceByIndex(
  unsigned int deviceIndex,
  TUsbAudioHandle* deviceHandle
	);


//
// close a device 
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_CloseDevice(
  TUsbAudioHandle deviceHandle
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_CloseDevice(
  TUsbAudioHandle deviceHandle
	);


//
// query USB IDs (vendor, product, revision, serial number etc.) and properties for a specific device
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetDeviceProperties(
  TUsbAudioHandle deviceHandle,
  TUsbAudioDeviceProperties* properties
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetDeviceProperties(
  TUsbAudioHandle deviceHandle,
  TUsbAudioDeviceProperties* properties
	);


//
// query device instance ID string
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetDeviceInstanceIdString(
  TUsbAudioHandle deviceHandle,
  WCHAR stringBuffer[],
  unsigned int stringBufferMaxChars
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetDeviceInstanceIdString(
  TUsbAudioHandle deviceHandle,
  WCHAR stringBuffer[],
  unsigned int stringBufferMaxChars
  );



//
// register for notifications on device state changes
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_RegisterDeviceNotification(
  TUsbAudioHandle deviceHandle,
  unsigned int categoryFilter,	// filter: bitwise OR of TUSBAUDIO_NOTIFY_CATEGORY_xxx constants
  HANDLE sharedEvent,					// NULL or auto-reset event, signaled when messages are available
  unsigned int flags					// reserved for future use, set to zero
	);
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_RegisterDeviceNotification(
  TUsbAudioHandle deviceHandle,
  unsigned int categoryFilter,
  HANDLE sharedEvent,
  unsigned int flags
	);



TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_ReadDeviceNotification(
  TUsbAudioHandle deviceHandle,
  TUsbAudioNotifyEvent* eventType,
	unsigned char* dataBuffer,
	unsigned int dataBufferSize,
	unsigned int* dataBytesReturned
	);
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_ReadDeviceNotification(
  TUsbAudioHandle deviceHandle,
  TUsbAudioNotifyEvent* eventType,
	unsigned char* dataBuffer,
	unsigned int dataBufferSize,
	unsigned int* dataBytesReturned
	);



//
// query sample rates supported by a specific device
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetSupportedSampleRates(
  TUsbAudioHandle deviceHandle,
  unsigned int sampleRateMaxCount,
  unsigned int sampleRateArray[],
  unsigned int* sampleRateCount
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetSupportedSampleRates(
  TUsbAudioHandle deviceHandle,
  unsigned int sampleRateMaxCount,
  unsigned int sampleRateArray[],
  unsigned int* sampleRateCount
	);


//
// query the current sample rate
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetCurrentSampleRate(
  TUsbAudioHandle deviceHandle,
  unsigned int* sampleRate
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetCurrentSampleRate(
  TUsbAudioHandle deviceHandle,
  unsigned int* sampleRate
	);


//
// set sample rate
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_SetSampleRate(
  TUsbAudioHandle deviceHandle,
  unsigned int sampleRate
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_SetSampleRate(
  TUsbAudioHandle deviceHandle,
  unsigned int sampleRate
	);


//
// query the set of clock sources that are available for a specific device
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetSupportedClockSources(
  TUsbAudioHandle deviceHandle,
  unsigned int clockSourceMaxCount,
  TUsbAudioClockSource clockSourceArray[],
  unsigned int* clockSourceCount
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetSupportedClockSources(
  TUsbAudioHandle deviceHandle,
  unsigned int clockSourceMaxCount,
  TUsbAudioClockSource clockSourceArray[],
  unsigned int* clockSourceCount
	);


//
// query the current clock source that is selected for a specific device
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetCurrentClockSource(
  TUsbAudioHandle deviceHandle,
  TUsbAudioClockSource* clockSource
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetCurrentClockSource(
  TUsbAudioHandle deviceHandle,
  TUsbAudioClockSource* clockSource
	);


//
// select the clock source of the specified device
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_SetCurrentClockSource(
  TUsbAudioHandle deviceHandle,
  unsigned int clockSourceId
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_SetCurrentClockSource(
  TUsbAudioHandle deviceHandle,
  unsigned int clockSourceId
	);


//
// query the set of input or output stream formats supported by the device
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetSupportedStreamFormats(
  TUsbAudioHandle deviceHandle,
	unsigned int inputStream,		// 1 = input format, 0 = output format
  unsigned int formatMaxCount,
  TUsbAudioStreamFormat formatArray[],
  unsigned int* formatCount
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetSupportedStreamFormats(
  TUsbAudioHandle deviceHandle,
	unsigned int inputStream,		// 1 = input format, 0 = output format
  unsigned int formatMaxCount,
  TUsbAudioStreamFormat formatArray[],
  unsigned int* formatCount
	);


//
// query the current input or output stream format
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetCurrentStreamFormat(
  TUsbAudioHandle deviceHandle,
	unsigned int inputStream,		// 1 = input format, 0 = output format
  TUsbAudioStreamFormat* format
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetCurrentStreamFormat(
  TUsbAudioHandle deviceHandle,
	unsigned int inputStream,		// 1 = input format, 0 = output format
  TUsbAudioStreamFormat* format
	);


//
// select the input or output stream format for a device
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_SetCurrentStreamFormat(
  TUsbAudioHandle deviceHandle,
	unsigned int inputStream,		// 1 = input format, 0 = output format
	unsigned int formatId
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_SetCurrentStreamFormat(
  TUsbAudioHandle deviceHandle,
	unsigned int inputStream,		// 1 = input format, 0 = output format
	unsigned int formatId
	);



//
// query the set of input or output channels, including properties of the channels
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetChannelProperties(
  TUsbAudioHandle deviceHandle,
	unsigned int inputChannels,		// 1 = input channel set, 0 = output channel set
  unsigned int channelMaxCount,
  TUsbAudioChannelProperty channelArray[],
  unsigned int* channelCount
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetChannelProperties(
  TUsbAudioHandle deviceHandle,
	unsigned int inputChannels,		// 1 = input channel set, 0 = output channel set
  unsigned int channelMaxCount,
  TUsbAudioChannelProperty channelArray[],
  unsigned int* channelCount
	);



//
// query the USB Configuration Descriptor of a specific device.
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetUsbConfigDescriptor(
  TUsbAudioHandle deviceHandle,
  unsigned char* descBuffer,
  unsigned int bufferSize,
  unsigned int* bytesReturned
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetUsbConfigDescriptor(
  TUsbAudioHandle deviceHandle,
  unsigned char* descBuffer,
  unsigned int bufferSize,
  unsigned int* bytesReturned
	);


//
// query the string of a specific USB String Descriptor of a specific device
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetUsbStringDescriptorString(
  TUsbAudioHandle deviceHandle,
  unsigned char stringIndex,
  int languageId,
  WCHAR descString[],
  unsigned int descStringMaxChars
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetUsbStringDescriptorString(
  TUsbAudioHandle deviceHandle,
  unsigned char stringIndex,
  int languageId,
  WCHAR descString[],
  unsigned int descStringMaxChars
  );


//
// send audio class SET request 
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_AudioControlRequestSet(
  TUsbAudioHandle deviceHandle,
  unsigned char entityID,
  unsigned char request,
  unsigned char controlSelector,
  unsigned char channelOrMixerControl,
  const void* paramBlock,					// optional, may be NULL
  unsigned int paramBlockLength,
  unsigned int* bytesTransferred,	// optional, may be NULL
  unsigned int timeoutMillisecs
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_AudioControlRequestSet(
  TUsbAudioHandle deviceHandle,
  unsigned char entityID,
  unsigned char request,
  unsigned char controlSelector,
  unsigned char channelOrMixerControl,
  const void* paramBlock,					// optional, may be NULL
  unsigned int paramBlockLength,
  unsigned int* bytesTransferred,	// optional, may be NULL
  unsigned int timeoutMillisecs
	);


//
// send audio class GET request 
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_AudioControlRequestGet(
  TUsbAudioHandle deviceHandle,
  unsigned char entityID,
  unsigned char request,
  unsigned char controlSelector,
  unsigned char channelOrMixerControl,
  void* paramBlock,								// optional, may be NULL
  unsigned int paramBlockLength,
  unsigned int* bytesTransferred,	// optional, may be NULL
  unsigned int timeoutMillisecs
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_AudioControlRequestGet(
  TUsbAudioHandle deviceHandle,
  unsigned char entityID,
  unsigned char request,
  unsigned char controlSelector,
  unsigned char channelOrMixerControl,
  void* paramBlock,								// optional, may be NULL
  unsigned int paramBlockLength,
  unsigned int* bytesTransferred,	// optional, may be NULL
  unsigned int timeoutMillisecs
	);



//
// send vendor or class control request with OUT data phase
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_ClassVendorRequestOut(
  TUsbAudioHandle deviceHandle,
  TUsbAudioControlRequestRecipient recipient,
  unsigned char isClassRequest,
  unsigned char bRequest,
  unsigned short wIndex,
  unsigned short wValue,
  unsigned short wLength,
  const void* dataBuffer,					// optional, may be NULL
  unsigned int* bytesTransferred,	// optional, may be NULL
  unsigned int timeoutMillisecs
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_ClassVendorRequestOut(
  TUsbAudioHandle deviceHandle,
  TUsbAudioControlRequestRecipient recipient,
  unsigned char isClassRequest,
  unsigned char bRequest,
  unsigned short wIndex,
  unsigned short wValue,
  unsigned short wLength,
  const void* dataBuffer,					// optional, may be NULL
  unsigned int* bytesTransferred,	// optional, may be NULL
  unsigned int timeoutMillisecs
  );


//
// send vendor or class control request with IN data phase
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_ClassVendorRequestIn(
  TUsbAudioHandle deviceHandle,
  TUsbAudioControlRequestRecipient recipient,
  unsigned char isClassRequest,
  unsigned char bRequest,
  unsigned short wIndex,
  unsigned short wValue,
  unsigned short wLength,
  void* dataBuffer,					// optional, may be NULL
  unsigned int* bytesTransferred,	// optional, may be NULL
  unsigned int timeoutMillisecs
  );
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_ClassVendorRequestIn(
  TUsbAudioHandle deviceHandle,
  TUsbAudioControlRequestRecipient recipient,
  unsigned char isClassRequest,
  unsigned char bRequest,
  unsigned short wIndex,
  unsigned short wValue,
  unsigned short wLength,
  void* dataBuffer,					// optional, may be NULL
  unsigned int* bytesTransferred,	// optional, may be NULL
  unsigned int timeoutMillisecs
  );



//
// query driver version info
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetDriverInfo(
  TUsbAudioDriverInfo* driverInfo
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetDriverInfo(
  TUsbAudioDriverInfo* driverInfo
	);



//
// query the current USB streaming mode (streaming buffer depth)
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetUsbStreamingMode(
  TUsbAudioUsbStreamingMode* usbStreamingMode
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetUsbStreamingMode(
  TUsbAudioUsbStreamingMode* usbStreamingMode
	);


//
// set a new USB streaming mode (streaming buffer depth)
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_SetUsbStreamingMode(
  TUsbAudioUsbStreamingMode usbStreamingMode
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_SetUsbStreamingMode(
  TUsbAudioUsbStreamingMode usbStreamingMode
	);


//
// query the current ASIO buffer size
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetASIOBufferSize(
  unsigned int* bufferSize			// in terms of samples
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetASIOBufferSize(
  unsigned int* bufferSize			// in terms of samples
	);


//
// set a new ASIO buffer size
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_SetASIOBufferSize(
  unsigned int bufferSize  // in terms of samples
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_SetASIOBufferSize(
  unsigned int bufferSize  // in terms of samples
	);


//
// based on the current USB streaming mode, 
// calculate the minimum ASIO buffer size for a given sample rate
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetMinimumASIOBufferSize(
	unsigned int sampleRate,
  unsigned int* minBufferSize			// in terms of samples
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetMinimumASIOBufferSize(
	unsigned int sampleRate,
  unsigned int* minBufferSize			// in terms of samples
	);




//
// query the current run mode of the USB device
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetDeviceUsbMode(
  TUsbAudioHandle deviceHandle,
	TUsbAudioDeviceRunMode* runMode
  );
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetDeviceUsbMode(
  TUsbAudioHandle deviceHandle,
	TUsbAudioDeviceRunMode* runMode
  );



//
// retrieve information on the streaming mode of the current device
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetDeviceStreamingMode(
  TUsbAudioHandle deviceHandle,
  TUsbAudioDeviceStreamingMode* streamingMode
	);
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetDeviceStreamingMode(
  TUsbAudioHandle deviceHandle,
  TUsbAudioDeviceStreamingMode* streamingMode
	);


//
// change the streaming mode of the current device
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_SetDeviceStreamingMode(
  TUsbAudioHandle deviceHandle,
  TUsbAudioDeviceStreamingMode streamingMode,
  unsigned int flags
	);
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_SetDeviceStreamingMode(
  TUsbAudioHandle deviceHandle,
  TUsbAudioDeviceStreamingMode streamingMode,
  unsigned int flags
	);



//
// Load a firmware image from the given buffer.
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_LoadFirmwareImageFromBuffer(
  const unsigned char* buffer,
  unsigned int numberOfBytes,
  unsigned int flags		// reserved for future use
  );
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_LoadFirmwareImageFromBuffer(
  const unsigned char* buffer,
  unsigned int numberOfBytes,
  unsigned int flags
  );


//
// Load a firmware image from the specified file.
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_LoadFirmwareImageFromFile(
  const WCHAR* fileName,
  unsigned int flags		// reserved for future use
  );
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_LoadFirmwareImageFromFile(
  const WCHAR* fileName,
  unsigned int flags
  );


//
// Query the size of the currently loaded image, if any.
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetFirmwareImageSize(
  unsigned int* numberOfBytes,
  unsigned int flags
  );
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetFirmwareImageSize(
  unsigned int* numberOfBytes,
  unsigned int flags
  );


//
// Unload the current firmware image.
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_UnloadFirmwareImage();
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_UnloadFirmwareImage();


//
// Return the firmware image that was retrieved from the USB device.
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetFirmwareImage(
  unsigned char* buffer,
  unsigned int bufferSize,
  unsigned int* bytesReturned,
  unsigned int flags		// reserved for future use
  );
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetFirmwareImage(
  unsigned char* buffer,
  unsigned int bufferSize,
  unsigned int* bytesReturned,
  unsigned int flags
  );


//
// Download the firmware image to the device.
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_StartDfuDownload(
  unsigned int deviceIndex,
	unsigned int targetIndex,
  unsigned int flags
  );
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_StartDfuDownload(
  unsigned int deviceIndex,
	unsigned int targetIndex,
  unsigned int flags
  );


//
// Retrieve the current firmware image from the device.
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_StartDfuUpload(
  unsigned int deviceIndex,
	unsigned int targetIndex,
  unsigned int flags		// reserved for future use
  );
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_StartDfuUpload(
  unsigned int deviceIndex,
	unsigned int targetIndex,
  unsigned int flags
  );


//
// Roll the firmware in the device back to the original factory image
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_StartDfuRevertToFactoryImage(
  unsigned int deviceIndex,
  unsigned int flags		// reserved for future use
  );
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_StartDfuRevertToFactoryImage(
  unsigned int deviceIndex,
  unsigned int flags		// reserved for future use
  );


//
// Check the status of the current DFU operation.
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetDfuStatus(
  TUsbAudioDfuProcState* downloadState,
  unsigned int* currentBytes,				// optional, may be NULL
  unsigned int* totalBytes,					// optional, may be NULL
  TUsbAudioStatus* completionStatus	// optional, may be NULL
  );
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetDfuStatus(
  TUsbAudioDfuProcState* downloadState,
  unsigned int* currentBytes,				// optional, may be NULL
  unsigned int* totalBytes,					// optional, may be NULL
  TUsbAudioStatus* completionStatus	// optional, may be NULL
  );

//
// Finalize the DFU operation.
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_EndDfuProc(void);
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_EndDfuProc(void);


//
// retrieve a property from the DSP plugin
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_GetDspProperty(
  TUsbAudioHandle deviceHandle,
  void* propertyBuffer,
  unsigned int propertySize
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_GetDspProperty(
  TUsbAudioHandle deviceHandle,
  void* propertyBuffer,
  unsigned int propertySize
	);

//
// set a property in the DSP plugin
//
TUSBAUDIO_DECL
TUsbAudioStatus
TUSBAUDIO_CALL
TUSBAUDIO_SetDspProperty(
  TUsbAudioHandle deviceHandle,
  const void* propertyBuffer,
  unsigned int propertySize
	);
// corresponding function type (useful for explicit loading with GetProcAddress)
typedef
TUsbAudioStatus
TUSBAUDIO_CALL
F_TUSBAUDIO_SetDspProperty(
  TUsbAudioHandle deviceHandle,
  const void* propertyBuffer,
  unsigned int propertySize
	);


//
// Convert status code to symbolic name.
// Returns a pointer to a null-terminated wide character string.
//
TUSBAUDIO_DECL
const WCHAR*
TUSBAUDIO_CALL
TUSBAUDIO_StatusCodeStringW(
	TSTATUS statusCode
	);
typedef
const WCHAR*
TUSBAUDIO_CALL
F_TUSBAUDIO_StatusCodeStringW(
	TSTATUS statusCode
	);


//
// Convert status code to symbolic name.
// Returns a pointer to a null-terminated ASCII character string.
//
TUSBAUDIO_DECL
const char*
TUSBAUDIO_CALL
TUSBAUDIO_StatusCodeStringA(
	TSTATUS statusCode
	);
typedef
const char*
TUSBAUDIO_CALL
F_TUSBAUDIO_StatusCodeStringA(
	TSTATUS statusCode
	);




#if defined (__cplusplus)
}
#endif


#endif  // __tusbaudioapi_h__

/*************************** EOF **************************************/
