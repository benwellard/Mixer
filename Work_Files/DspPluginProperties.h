/************************************************************************
 *
 *  Module:       DspPluginProperties.h
 *  Description:  properties supported by the DSP plugin
 *
 *  Runtime Env.: any
 *                
 *  Author(s):
 *    Udo Eberhardt,  Udo.Eberhardt@thesycon.de
 *  Company:
 *    Thesycon GmbH, Germany      http://www.thesycon.de
 *                
 ************************************************************************/

#ifndef __DspPluginProperties_h__
#define __DspPluginProperties_h__

#include "dsp_types.h"


// struct alignment = 1 byte
#include <pshpack1.h>

#if defined(__cplusplus) && defined(TUSBAUDIO_NAMESPACE)
namespace TUSBAUDIO_NAMESPACE {
#endif

//
// This file defines the property based control interface supported by
// the sample DSP plugin. The sample DSP plugin implements a very simple 
// echo effect for all output channels. 
//
// A custom plugin can define its own properties and associated data structures.
//


//
// property identifiers
//
typedef enum tagDspProperty
{
	DspProperty_OutChannelCount,	// get only
	DspProperty_InChannelCount,		// get only

	// echo effect
	DspProperty_MaxDelay,					// get only
	DspProperty_Delay,						// get/set
	DspProperty_Amplification,		// get/set

	// monitor mixer
	DspProperty_AmpInput					// get/set

} DspProperty;



//
// data structures passed from/to plugin
//

typedef struct tagDspDelayData
{
	unsigned int channelIndex;
	unsigned int delayMilliseconds;
} DspDelayData;

typedef struct tagDspAmpData
{
	unsigned int channelIndex;
	unsigned int amplification;
			// amplification, 0.0..1.0 in units of 1/1000
			// a value of 1000 means amp = 1.0
			// a value of  500 means amp = 0.5
			// a value of  100 means amp = 0.1
			// a value of    0 means amp = 0.0
} DspAmpData;



// common header for all data structs
typedef struct tagDspProp
{
	DspProperty propertyId;
} DspProp;


// DspProperty_OutChannelCount
// DspProperty_InChannelCount
typedef struct tagDspPropData_ChannelCount
{
	DspProp prop;

	unsigned int channelCount;
} DspPropData_ChannelCount;


// DspProperty_MaxDelay
typedef struct tagDspPropData_MaxDelay
{
	DspProp prop;

	unsigned int maxDelayMilliseconds;
} DspPropData_MaxDelay;


// DspProperty_Delay
typedef struct tagDspPropData_Delay
{
	DspProp prop;

	unsigned int count;
	DspDelayData delayData[DSP_MAX_CHANNELS];
} DspPropData_Delay;


// DspProperty_Amplification
// DspProperty_AmpInput
typedef struct tagDspPropData_Amplification
{
	DspProp prop;

	unsigned int count;
	DspAmpData ampData[DSP_MAX_CHANNELS];
} DspPropData_Amplification;

#if defined(__cplusplus) && defined(TUSBAUDIO_NAMESPACE)
}
#endif

// restore previous alignment
#include <poppack.h>


#endif // __DspPluginProperties_h__

/******************************** EOF ***********************************/
