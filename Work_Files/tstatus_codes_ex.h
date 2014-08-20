/************************************************************************
 *
 *  Module:       tstatus_codes_ex.h
 *
 *  Description:
 *    Project-specific status code definitions used by both 
 *    kernel-mode and user-mode software layers.
 *
 *  Runtime Env.: Win32 / NT Kernel
 *
 *  Author(s):   
 *    Udo Eberhardt,  Udo.Eberhardt@thesycon.de
 *                
 *  Companies:
 *    Thesycon GmbH
 *                
 ************************************************************************/

//
// This file must be included by tstatus_codes.h only.
//
#ifndef __inside_tstatus_codes_h__
#error This file is an extension to tstatus_codes.h and must not be included otherwise.
#endif



///////////////////////////////////////////////////////////////////
// project-specific status codes
// A set of project-specific status codes may be defined per project.
// The project-specific status codes values have to use the range from
// 0x1000 ... 0x1FFF.
// Under Windows this is mapped to 
// 0xE0001000 ... 0xE0001FFF
///////////////////////////////////////////////////////////////////

#define				TSTATUS_SOUND_DEVICE_IN_USE						TSTATUS_CODE(0x1001)
case_TSTATUS_(TSTATUS_SOUND_DEVICE_IN_USE, "")

#define				TSTATUS_ASIO_IN_USE										TSTATUS_CODE(0x1002)
case_TSTATUS_(TSTATUS_ASIO_IN_USE, "")

#define				TSTATUS_INVALID_SAMPLE_SIZE						TSTATUS_CODE(0x1003)
case_TSTATUS_(TSTATUS_INVALID_SAMPLE_SIZE, "")

#define				TSTATUS_INVALID_SAMPLE_RATE						TSTATUS_CODE(0x1004)
case_TSTATUS_(TSTATUS_INVALID_SAMPLE_RATE, "")

#define				TSTATUS_SAMPLE_RATE_NOT_SUPPORTED			TSTATUS_CODE(0x1005)
case_TSTATUS_(TSTATUS_SAMPLE_RATE_NOT_SUPPORTED, "")

#define				TSTATUS_CANNOT_OPEN_INI_FILE					TSTATUS_CODE(0x1006)
case_TSTATUS_(TSTATUS_CANNOT_OPEN_INI_FILE, "")

#define				TSTATUS_NO_IMAGE_LOADED								TSTATUS_CODE(0x1007)
case_TSTATUS_(TSTATUS_NO_IMAGE_LOADED, "")

#define				TSTATUS_INVALID_AUDIO_FUNCTION				TSTATUS_CODE(0x1008)
case_TSTATUS_(TSTATUS_INVALID_AUDIO_FUNCTION, "")


//!!! low byte contains T_UsbClsDfu_GetStatusResponse.bStatus
#define				TSTATUS_DFU_STATE_ERROR								TSTATUS_CODE(0x1100)
case_TSTATUS_(TSTATUS_DFU_STATE_ERROR, "")
//#define				TSTATUS_DFU_STATE_ERROR_LAST				TSTATUS_CODE(0x11FF)



/*************************** EOF **************************************/
