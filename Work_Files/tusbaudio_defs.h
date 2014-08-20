/************************************************************************
 *
 *  Module:       tusbaudio_defs.h
 *
 *  Description:
 *    Types and definitions for the programming interface provided by the 
 *    device driver.
 *    This file conforms to C standard. It can be used by C and C++ code.
 *                
 *  Runtime Env.: 
 *    Windows XP Kernel, Win32
 *
 *  Company:
 *    Thesycon GmbH, Germany      http://www.thesycon.de
 *
 ************************************************************************/

#ifndef __tusbaudio_defs_h__
#define __tusbaudio_defs_h__


// max length, in chars, of strings reported by the device, including terminating null
#define TUSBAUDIO_MAX_STRDESC_STRLEN							128

// maximum length of display name strings, including terminating null
#define TUSBAUDIO_MAX_NAME_STRING_LENGTH					TUSBAUDIO_MAX_STRDESC_STRLEN

// max length, in bytes, of the data field that may be attached to a Notification Event
#define TUSBAUDIO_NOTIFY_EVENT_MAX_DATA_BYTES			64


//
// Notification Event categories
//
// note: values can be combined bitwise OR
//
#define TUSBAUDIO_NOTIFY_CATEGORY_NONE											0x00000000U
#define TUSBAUDIO_NOTIFY_CATEGORY_ALL												0xFFFFFFFFU
#define TUSBAUDIO_NOTIFY_CATEGORY_SAMPLE_RATE_CHANGE				0x00000001U
#define TUSBAUDIO_NOTIFY_CATEGORY_STREAM_CHANGE							0x00000002U
#define TUSBAUDIO_NOTIFY_CATEGORY_VOLUME_CHANGE							0x00000004U
#define TUSBAUDIO_NOTIFY_CATEGORY_AC_NODE_INTERRUPT					0x00010000U


//
// Notification Events
//
typedef enum tagTUsbAudioNotifyEvent 
{
	NotifyEvent_SampleRateChanged = 1,		// category = TUSBAUDIO_NOTIFY_CATEGORY_SAMPLE_RATE_CHANGE

	NotifyEvent_StreamFormatChanged,			// category = TUSBAUDIO_NOTIFY_CATEGORY_STREAM_CHANGE

	NotifyEvent_VolumeChanged,						// category = TUSBAUDIO_NOTIFY_CATEGORY_VOLUME_CHANGE
	NotifyEvent_MuteChanged,							// category = TUSBAUDIO_NOTIFY_CATEGORY_VOLUME_CHANGE

	NotifyEvent_AcNodeInterrupt = 100			// category = TUSBAUDIO_NOTIFY_CATEGORY_AC_NODE_INTERRUPT
	
} TUsbAudioNotifyEvent;


//
// data field for NotifyEvent_VolumeChanged and NotifyEvent_MuteChanged events
//
// NOTE: This struct layout is part of the API. If it is changed, the API version needs to be changed.
//
typedef struct tagTUsbAudioNotifyVolumeChange
{
	// unit ID of the feature unit that has a change in volume or mute
	// corresponds to TUsbAudioChannelProperty.featureUnitId
	unsigned char featureUnitId;
	// channel number of the channel that has a change in volume or mute
	// 0 for master, 1..N for logical channels
	unsigned char featureUnitLogicalChannel;
	
	// new value for volume or mute
	// for NotifyEvent_VolumeChanged messages this field contains the volume value set for channel
	// for NotifyEvent_MuteChanged messages this field is set to one if the channel is muted and to zero otherwise
	short newValue;
	
	// reserved for future use
	unsigned int reserved[8];

} TUsbAudioNotifyVolumeChange;


//
// driver version info
//
// NOTE: This struct layout is part of the API. If it is changed, the API version needs to be changed.
//
typedef struct tagTUsbAudioDriverInfo
{
	// current version of programming interface (API) exposed by DLL
  unsigned int apiVersionMajor;
  unsigned int apiVersionMinor;

  // current version of device driver implementation
  unsigned int driverVersionMajor;
  unsigned int driverVersionMinor;
  unsigned int driverVersionSub;

  // additional information, encoded as bit flags
  unsigned int flags;
// the device driver is a debug build
#define TUSBAUDIO_DRIVER_INFOFLAG_CHECKED_BUILD    0x00000001
// the device driver is an evaluation version
#define TUSBAUDIO_DRIVER_INFOFLAG_EVAL_VERSION	   0x00000002
// the device driver is the Lite version
#define TUSBAUDIO_DRIVER_INFOFLAG_LITE_VERSION	   0x00000004

} TUsbAudioDriverInfo;


//
// device properties
//
// NOTE: This struct layout is part of the API. If it is changed, the API version needs to be changed.
//
typedef struct tagTUsbAudioDeviceProperties
{
 	// values from the USB device descriptor
	unsigned int usbVendorId;
	unsigned int usbProductId;
	unsigned int usbRevisionId;

	// serial number as reported by the device (string descriptor)
	// set to an empty string if the device does not support a serial number
  WCHAR serialNumberString[TUSBAUDIO_MAX_STRDESC_STRLEN];

	// manufacturer and product name as reported by the device (string descriptor)
	// always contains a null-terminated string,
	// set to an empty string if the device does not support it
  WCHAR manufacturerString[TUSBAUDIO_MAX_STRDESC_STRLEN];
  WCHAR productString[TUSBAUDIO_MAX_STRDESC_STRLEN];

  // various flags bit-encoded
  unsigned int flags;
#define TUSBAUDIO_DEVPROP_FLAG_HIGH_SPEED_SUPPORTED		0x00000001	// device supports high-speed mode
#define TUSBAUDIO_DEVPROP_FLAG_HIGH_SPEED							0x00000002	// device currently works in high-speed mode
#define TUSBAUDIO_DEVPROP_FLAG_DFU_SUPPORTED					0x00000010	// device supports USB DFU class
#define TUSBAUDIO_DEVPROP_FLAG_DSP_PLUGIN_PRESENT			0x00000020	// DSP plugin is loaded
#define TUSBAUDIO_DEVPROP_FLAG_AUDIOCLASS10_SUPPORTED	0x00000100	// device supports USB Audio Class 1.0
#define TUSBAUDIO_DEVPROP_FLAG_AUDIOCLASS20_SUPPORTED	0x00000200	// device supports USB Audio Class 2.0

	// reserved for future use
	unsigned int reserved[64];

} TUsbAudioDeviceProperties;



// min ASIO buffer size, in samples, we do support
#define TUSBAUDIO_MIN_ASIO_BUFFER_SIZE_SMP			(16)       // samples
// max ASIO buffer size, in samples, we do support
#define TUSBAUDIO_MAX_ASIO_BUFFER_SIZE_SMP			(64*1024)  // samples


//
// USB Streaming Mode (streaming buffer size)
//
typedef enum tagTUsbAudioUsbStreamingMode
{
	UsbStreamingMode_reserved = 0,	// for internal use only, not a real value

	UsbStreamingMode_MinLat	= 1,			//  1 ms --> minimum latency
	UsbStreamingMode_LowLat = 2,			//  2 ms --> low latency
	UsbStreamingMode_Standard = 4,		//  4 ms --> works on most PCs
	UsbStreamingMode_Relaxed = 8,			//  8 ms --> more tolerant towards kernel-mode DPC jitter
	UsbStreamingMode_Reliable = 12,		// 12 ms --> more tolerant towards kernel-mode DPC jitter
	UsbStreamingMode_Safe = 16,				// 16 ms --> even more tolerant towards kernel-mode DPC jitter
	UsbStreamingMode_ExtraSafe = 32		// 32 ms --> most robust but poor latency, use for HIFI playback for example

} TUsbAudioUsbStreamingMode;




//
// device streaming mode
//
typedef enum tagTUsbAudioDeviceStreamingMode 
{
	DeviceStreamingMode_reserved = 0,	// for internal use only, not a real value

	DeviceStreamingMode_PowerSaver,
	DeviceStreamingMode_AlwaysOn,

	DeviceStreamingMode_last	// for internal use only, not a real value

} TUsbAudioDeviceStreamingMode;

// flags
#define TUSBAUDIO_STREAMING_MODE_PERSISTENT		0x00000001



//
// Clock Source Type
//
typedef enum tagTUsbAudioClockSourceType 
{
	ClockSourceType_External = 1,

	ClockSourceType_InternalFixed,
	ClockSourceType_InternalVariable,
	ClockSourceType_InternalProgrammable

} TUsbAudioClockSourceType;

//
// clock source info
//
// NOTE: This struct layout is part of the API. If it is changed, the API version needs to be changed.
//
typedef struct tagTUsbAudioClockSource
{
  // unique ID
  // This ID unambiguously identifies the clock source at the driver API.
  // Values are driver-defined. Client code must not interpret the value.
	unsigned int clockSourceId;

  // ID of the clock source unit (within the audio function) that implements this source.
	unsigned int clockSourceUnitId;

	// clock selector input pin this source is connected to
	unsigned int clockSelectorPinNumber;
	
	// flag: 1 if clock is valid/stable, 0 otherwise
	unsigned int clockIsValid;

  // current sample rate, in samples per second
  // only valid if clockIsValid==1, set to zero otherwise
  unsigned int sampleRate;

	// name of the clock source
	WCHAR clockNameString[TUSBAUDIO_MAX_STRDESC_STRLEN];
	
	// type of the clock source
	TUsbAudioClockSourceType clockSourceType;

  // current sample rate of signal of associated external terminal
  // set to zero if not available
  unsigned int externalSampleRate;
  
  // various flags, bit-encoded
  unsigned int flags;
#define TUSBAUDIO_CLOCK_SYNCHED_SOF				0x00000001

	// reserved for future use
	unsigned int reserved[13];

} TUsbAudioClockSource;




//
// stream format info
//
// NOTE: This struct layout is part of the API. If it is changed, the API version needs to be changed.
//
typedef struct tagTUsbAudioStreamFormat
{
  // unique ID
  // This ID unambiguously identifies the format at the driver API.
  // Values are driver-defined. Client code should not interpret the value.
	unsigned int formatId;

  // number of valid bits per sample (16 or 24)
	unsigned int bitsPerSample;

	// number of audio channels
	unsigned int numberOfChannels;

	// name of the format as reported by the device
	WCHAR formatNameString[TUSBAUDIO_MAX_STRDESC_STRLEN];

	// reserved for future use
	unsigned int reserved[16];

} TUsbAudioStreamFormat;



//
// channel property
//
// NOTE: This struct layout is part of the API. If it is changed, the API version needs to be changed.
//
typedef struct tagTUsbAudioChannelProperty
{
	// zero-based index within the stream
	unsigned int channelIndex;

	// 1 for input (record), 0 for output (playback)
	unsigned int isInput;

  // various flags, bit-encoded
  unsigned int flags;
#define TUSBAUDIO_CHANPROP_FLAG_VOLUME_MAPPED				0x00000001	// KS volume control is mapped to the below FU
#define TUSBAUDIO_CHANPROP_FLAG_MUTE_MAPPED					0x00000002	// KS mute control is mapped to the below FU

	// ID of the feature unit (FU) that is used by KS to control volume and/or mute
	// valid only if one of TUSBAUDIO_CHANPROP_FLAG_VOLUME_MAPPED or TUSBAUDIO_CHANPROP_FLAG_MUTE_MAPPED is set
	unsigned char featureUnitId;
	// logical channel in the corresponding feature unit
	unsigned char featureUnitLogicalChannel;
	
	// supported range for volume control, values as defined by the USB Audio Class specification
	// valid only if TUSBAUDIO_CHANPROP_FLAG_VOLUME_MAPPED is set
	short volumeRangeMin;
	short volumeRangeMax;
	// supported resolution for volume values, values as defined by the USB Audio Class specification
	// valid only if TUSBAUDIO_CHANPROP_FLAG_VOLUME_MAPPED is set
	unsigned short volumeRangeStep;

	// channel name as reported by the device
	WCHAR channelNameString[TUSBAUDIO_MAX_STRDESC_STRLEN];

	// reserved for future use
	unsigned int reserved[16];

} TUsbAudioChannelProperty;



typedef enum tagTUsbAudioControlRequestRecipient 
{
  ControlRequestRecipient_Device = 0,
  ControlRequestRecipient_Interface,
  ControlRequestRecipient_Endpoint,
  ControlRequestRecipient_Other
} TUsbAudioControlRequestRecipient;



#endif  // __tusbaudio_defs_h__

/*************************** EOF **************************************/
