/************************************************************************
 *
 *  Module:       dsp_types.h
 *  Description:  data types and other defs used by DSP and driver code
 *
 *  Runtime Env.: kernel mode
 *                
 *  Author(s):
 *    Udo Eberhardt,  Udo.Eberhardt@thesycon.de
 *  Company:
 *    Thesycon GmbH, Germany      http://www.thesycon.de
 *                
 ************************************************************************/

#ifndef __dsp_types_h__
#define __dsp_types_h__


// max number of channels supported by the data path routed through the DSP plugin
#define DSP_MAX_CHANNELS		64


//
// generic sample, contains either PCM or FLOAT format
//
typedef int GenSample32b;
// idle value
#define GEN_SAMPLE_32b_IDLE		0


//
// Integer type the driver uses to represent a 32 bit LPCM sample.
// 32 bit signed integer:
//   bits 31..0 = sample word, bit 31 = sign bit
//
typedef int LpcmSample32b;
// idle value
#define LPCM_SAMPLE_32b_IDLE		0


//
// IEEE 754 float type, 32 bits
//
typedef float FloatSample32b;
// idle value
#define FLOAT_SAMPLE_32b_IDLE		0.0f





//
// sample formats reported by the device
//
enum DeviceSampleFormat
{
	SampleFormat_unknown = 0,
	SampleFormat_PCM8 = 8,				// PCM,  8 valid bits
	SampleFormat_PCM16 = 16,			// PCM, 16 valid bits
	SampleFormat_PCM24 = 24,			// PCM, 24 valid bits
	SampleFormat_PCM32 = 32,			// PCM, 32 valid bits
	SampleFormat_IEEE_FLOAT	= 754	// IEEE 754 float, 32 bits
};



//
// We define a set of integer types of a known size one both compilers, MS and GNU (Mac)
//

// 64 bit size on both x86 and x64
typedef long long DSP_INT64;
typedef unsigned long long DSP_UINT64;

// 32 bit size on both x86 and x64
typedef int DSP_INT32;
typedef unsigned int DSP_UINT32;

// 16 bit size on both x86 and x64
typedef short DSP_INT16;
typedef unsigned int DSP_UINT16;

// 8 bit size on both x86 and x64
typedef char DSP_INT8;
typedef unsigned char DSP_UINT8;




#endif // __dsp_types_h__

/******************************** EOF ***********************************/
