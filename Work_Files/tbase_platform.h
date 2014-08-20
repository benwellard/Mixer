/************************************************************************
 *
 *  Module:       tbase_platform.h
 *  Description:
 *     platform detection/adaption
 *
 *  Author(s):   
 *    Frank Hoffmann
 *                
 *  Companies:
 *    Thesycon GmbH, Germany      http://www.thesycon.de
 *                
 ************************************************************************/

#ifndef __tbase_platform_h__
#define __tbase_platform_h__

/*
	This file automatically detects the following settings.
	Client code can use these symbols to implement compile-time decisions.
	
	TB_DEBUG
	  Defined as 1 if this is a debug build.
	  Defined as 0 if this is a release build.
	  Embedded environment: Must be defined in the build files (Makefile etc.)
	  Visual Studio: Will automatically be derived from DBG _DEBUG etc.
	usage:
		#if TB_DEBUG
		#endif


	TBASE_LITTLE_ENDIAN
		defined if target platform is little endian
	usage:
		#ifdef TBASE_LITTLE_ENDIAN
		#endif

	TBASE_BIG_ENDIAN
		defined if target platform is big endian
	usage:
		#ifdef TBASE_BIG_ENDIAN
		#endif

	TBASE_ARCH_32BIT
		defined if the target architecture is 32 bit.
	usage:
		#ifdef TBASE_ARCH_32BIT
		#endif

	TBASE_ARCH_64BIT
		defined if the target architecture is 64 bit.
	usage:
		#ifdef TBASE_ARCH_64BIT
		#endif


	TBASE_COMPILER_MICROSOFT
		defined if Microsoft compiler is detected.
	usage:
		#ifdef TBASE_COMPILER_MICROSOFT
		#endif

	TBASE_COMPILER_MICROSOFT_KERNEL_MODE 
		defined if Windows kernel mode

	TBASE_COMPILER_MICROSOFT_USER_MODE 
		defined if Windows user mode (Win32)

	TBASE_COMPILER_MICROSOFT_UNDER_CE 
		defined if Windows CE


	TBASE_COMPILER_GNU
		defined if GNU compiler is detected.
		A more specific symbol is defined in addition to TBASE_COMPILER_GNU, see below.
	usage:
		#ifdef TBASE_COMPILER_GNU
		#endif

	TBASE_COMPILER_ARM
		defined if ARM (Keil) compiler is detected.
	usage:
		#ifdef TBASE_COMPILER_ARM
		#endif

	TBASE_COMPILER_C99
		defined if the compiler is C99 compliant
	usage:
		#ifdef TBASE_COMPILER_C99
		#endif


	TBASE_AL_CALL
		defines the compiler/platform specific calling convention for functions in tbase_al.h

	TB_INLINE
		wrapper for the inline keyword, see below for compiler specifics

	TB_IRQ_HANDLER
		compiler specific function modifier to be used for interrupt service routines
	

	This file also defines the following helper macros:
	TB_COMPILE_TIME_ASSERT(expression)
	TB_CHECK_SIZEOF(type, expected_size)
	
	TB_FUNC
		macro that resolves to current function name
		Note: TB_FUNC is like a predefined identifier and corresponds to
			const char TB_FUNC[] = "MyFunction";
		Thus, string concatenation does not work and it must be used this way:
			printf("%s: blabla", TB_FUNC);
*/


/* in C++ mode, use standard inline keyword */
#if defined(__cplusplus)
#define TB_INLINE	inline
#endif


/******* Microsoft *******/
#ifndef TBASE_COMPILER_DETECTED
#if defined(_MSC_VER) || defined(RC_INVOKED)	// includes RC
	/* Microsoft compiler detected */
	#define TBASE_COMPILER_MICROSOFT
	#define TBASE_COMPILER_DETECTED
	#define TB_FUNC __FUNCTION__
	#define TBASE_AL_CALL __stdcall
	#ifndef TB_INLINE
	#define TB_INLINE	__inline
	#endif

	#ifdef UNDER_CE
		/* Windows CE */
		#define TBASE_COMPILER_MICROSOFT_UNDER_CE
		#define TBASE_COMPILER_MICROSOFT_USER_MODE
	#else
		#if defined(__BUILDMACHINE__) || defined(ENV_KERNEL_MODE)
			/* Windows kernel mode */
			#define TBASE_COMPILER_MICROSOFT_KERNEL_MODE
		#else
			/* Windows user mode */
			#define TBASE_COMPILER_MICROSOFT_USER_MODE
		#endif
	#endif

	/* always little endian */
	#ifndef TBASE_LITTLE_ENDIAN
		#define TBASE_LITTLE_ENDIAN
	#endif
	#if defined(TBASE_BIG_ENDIAN)
		#error Microsoft compiler is not big endian.
	#endif

	#if defined(_M_X64)
		#define TBASE_ARCH_64BIT
	#else
		#define TBASE_ARCH_32BIT
	#endif

	// DBG is always defined, either as 0 or 1, newer WDKs seem not to define DBG on free builds
	#ifndef DBG
	#define DBG 0
	#endif

	/* detect debug or release build */
	#ifndef TB_DEBUG
		#if DBG || defined(_DEBUG) || defined(DEBUG)
		#define TB_DEBUG 1
		#else
		#define TB_DEBUG 0
		#endif
	#endif

#endif
#endif /* #ifndef TBASE_COMPILER_DETECTED */


/******* GNU/APPLE *******/
#ifndef TBASE_COMPILER_DETECTED
#if defined(__GNUC__) && defined(APPLE)
	#define TBASE_COMPILER_GNU
	#define TBASE_COMPILER_APPLE
	#define TBASE_COMPILER_DETECTED
	#define TB_FUNC __PRETTY_FUNCTION__
	#ifndef TB_INLINE
	#define TB_INLINE	inline
	#endif
	/* we assume Intel CPU, always little endian */
	#ifndef TBASE_LITTLE_ENDIAN
		#define TBASE_LITTLE_ENDIAN
	#endif
	#if defined(TBASE_BIG_ENDIAN)
		#error Apple/Intel is not big endian.
	#endif
    #if defined(__amd64__)
        #define TBASE_ARCH_64BIT
    #else
        #define TBASE_ARCH_32BIT
    #endif
	/* default on GNU: no calling convention */
	#define TBASE_AL_CALL
	/*#define TBASE_AL_CALL __attribute__((cdecl))*/
#endif /* APPLE */
#endif /* #ifndef TBASE_COMPILER_DETECTED */


/******* GNU/Linux *******/
#ifndef TBASE_COMPILER_DETECTED
#if defined(__GNUC__) && defined(__linux__)
	#define TBASE_COMPILER_GNU
	#define TBASE_COMPILER_LINUX
	#define TBASE_COMPILER_DETECTED
	#define TB_FUNC __PRETTY_FUNCTION__
	#ifndef TB_INLINE
	#define TB_INLINE	inline
	#endif
	/* default on GNU: no calling convention */
	#define TBASE_AL_CALL
	#if defined(__i386__) || defined(__amd64__)
		/* Intel: defaults to little endian */
		#ifndef TBASE_LITTLE_ENDIAN
			#define TBASE_LITTLE_ENDIAN
		#endif
		#if defined(TBASE_BIG_ENDIAN)
			#error Linux/Intel is not big endian.
		#endif
		#if defined(__amd64__)
			#define TBASE_ARCH_64BIT
		#else
			#define TBASE_ARCH_32BIT
		#endif
	#else
		/* unknown: e.g. ARM */
		#error unknown GNU/Linux variant
	#endif
#endif
#endif /* #ifndef TBASE_COMPILER_DETECTED */



/******* GNU/AVR32 *******/
#ifndef TBASE_COMPILER_DETECTED
#if defined(__GNUC__) && defined(__AVR32__)
	#define TBASE_COMPILER_GNU
	#define TBASE_COMPILER_AVR32
	#define TBASE_COMPILER_DETECTED
	#define TB_FUNC __FUNCTION__
	/* always big endian */
	#ifndef TBASE_BIG_ENDIAN
		#define TBASE_BIG_ENDIAN
	#endif
	#if defined(TBASE_LITTLE_ENDIAN)
		#error AVR32 compiler is not little endian.
	#endif
	#define TBASE_ARCH_32BIT
	/* default on GNU: no calling convention */
	#define TBASE_AL_CALL
#endif /* AVR32 */
#endif /* #ifndef TBASE_COMPILER_DETECTED */


/******* ARMCC + Keil *******/
#ifndef TBASE_COMPILER_DETECTED
#if defined(__arm__) && defined(__CC_ARM) && defined(__ARMCC_VERSION)
	#define TBASE_COMPILER_ARM
	#define TBASE_COMPILER_DETECTED
	#define TB_FUNC __FUNCTION__
	/* little or big endian */
	#if !defined(TBASE_BIG_ENDIAN) && !defined(TBASE_LITTLE_ENDIAN)
		#ifdef __BIG_ENDIAN
		#define TBASE_BIG_ENDIAN
		#else
		#define TBASE_LITTLE_ENDIAN
		#endif
	#endif
	#define TBASE_ARCH_32BIT
	/* ISR modifier */
	#define TB_IRQ_HANDLER __irq
	/* no calling convention */
	#define TBASE_AL_CALL
	/* inline keyword */
	#ifndef TB_INLINE
	#define TB_INLINE	__forceinline
	#endif
#endif
#endif /* #ifndef TBASE_COMPILER_DETECTED */


/******* GNU ARM *******/
#ifndef TBASE_COMPILER_DETECTED
#if defined(__arm__) && defined(__GNUC__)
	#define TBASE_COMPILER_GNU
	#define TBASE_COMPILER_GNUARM
	#define TBASE_COMPILER_DETECTED
	#define TB_FUNC __PRETTY_FUNCTION__
	/* ARM may be little or big endian */
	#if !defined(TBASE_BIG_ENDIAN) && !defined(TBASE_LITTLE_ENDIAN)
		#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
		#define TBASE_LITTLE_ENDIAN
		#else
		#define TBASE_BIG_ENDIAN
		#endif
	#endif
	#define TBASE_ARCH_32BIT
	/* default on GNU: no calling convention */
	#define TBASE_AL_CALL
	/* inline keyword */
	#ifndef TB_INLINE
	#define TB_INLINE	inline
	#endif
#endif
#endif /* #ifndef TBASE_COMPILER_DETECTED */



/******* TI TMS470 *******/
#ifndef TBASE_COMPILER_DETECTED
#if defined(__TMS470__)
	/* ARM Optimizing C/C++ Compiler (Texas Instruments/TMS470) */
	/* __GNUC__ may or may not be defined */
	#define TBASE_COMPILER_TMS470
	#define TBASE_COMPILER_DETECTED
	#define TB_FUNC __FUNCTION__
	#if !defined(TBASE_BIG_ENDIAN) && !defined(TBASE_LITTLE_ENDIAN)
		#ifdef _big_endian__
		#define TBASE_BIG_ENDIAN
		#else
		#define TBASE_LITTLE_ENDIAN
		#endif
	#endif
	#define TBASE_ARCH_32BIT
	/* no calling convention */
	#define TBASE_AL_CALL
	/* TI compilers do not currently support the #pragma pack construct */
	/* packing must be applied individually */
	//#define TB_PACK_STRUCT_TYPE __attribute__ ((packed))
	/* disable TB_CHECK_SIZEOF macro until the packing/sizeof issues for this compiler are solved*/
	#define TB_CHECK_SIZEOF(type,size)
#endif /* __TMS470__ */
#endif /* #ifndef TBASE_COMPILER_DETECTED */



#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#define TBASE_COMPILER_C99
/* C99 defines the standard inline keyword */
#ifndef TB_INLINE
#define TB_INLINE	inline
#endif
#endif


/*
 * some checks
 */
#define TB_DEBUG 0
#define TBASE_LITTLE_ENDIAN
#define TBASE_ARCH_32BIT
#define TBASE_COMPILER_DETECTED
#ifndef TB_DEBUG
	#error TB_DEBUG must be defined. Add either TB_DEBUG=0 or TB_DEBUG=1 to your makefile or project settings.
#endif

#if !defined(TBASE_COMPILER_DETECTED)
	#error Compiler not detected.
#endif

#if defined(TBASE_BIG_ENDIAN) && defined(TBASE_LITTLE_ENDIAN)
	#error Both little and big endian are defined.
#endif

#if !defined(TBASE_BIG_ENDIAN) && !defined(TBASE_LITTLE_ENDIAN)
	#error Either little or big endian must be defined.
#endif

#if defined(TBASE_ARCH_32BIT) && defined(TBASE_ARCH_64BIT)
	#error Both 32 bit and 64 bit arch are defined.
#endif

#if !defined(TBASE_ARCH_32BIT) && !defined(TBASE_ARCH_64BIT)
	#error Either 32 bit or 64 bit arch must be defined.
#endif

#if !defined(TB_INLINE)
	#error TB_INLINE not defined for this compiler.
#endif

#if !defined(TB_FUNC)
	#define TB_FUNC ""
#endif


/* 
 Include standard header files to get standard types and macros:
   size_t
   ptrdiff_t
   wchar_t
   NULL
   offsetof
*/
#if defined(__cplusplus)
	#if defined(APPLE)
		#include <sys/types.h>
	#else
		#include <cstddef>
		#if defined (TBASE_COMPILER_ARM)
			// required for ARM compiler: make size_t available in global namespace
			using std::size_t;
			using std::ptrdiff_t;
		#endif
	#endif
#else
#include <stddef.h>
#endif


/*
 * some basic utilities
 */


/*
 * TB_COMPILE_TIME_ASSERT() can be used to perform many compile-time assertions:
 * type sizes, field offsets, etc.
 * An assertion failure results in error C2118: negative subscript.
 */
#ifdef _lint
/* don't confuse lint with this special stuff */
/*lint -emacro( {19}, TB_COMPILE_TIME_ASSERT) */
#ifdef TB_COMPILE_TIME_ASSERT
#undef TB_COMPILE_TIME_ASSERT
#endif
#define TB_COMPILE_TIME_ASSERT(exp)
#else

/* default implementation, active if TB_COMPILE_TIME_ASSERT was not defined in the compiler-specific section above */
#ifndef TB_COMPILE_TIME_ASSERT
/* we use an external variable declaration, original code, found in the internet: */
/* extern char (*tb_check_sizeof(void)) [sizeof(char[1 - 2*!(sizeof(type)==(size))])] */
/* if __COUNTER__ is supported by the compiler then we use it to generate unique identifiers */
#ifdef __COUNTER__
#define TB_COMPILE_TIME_ASSERT(exp)	TB_COMPILE_TIME_ASSERT_TAG((exp), __COUNTER__)
#else
#define TB_COMPILE_TIME_ASSERT(exp)	TB_COMPILE_TIME_ASSERT_TAG((exp), 0)
#endif
/* use this variant with a unique tag name if linkage specifier conflicts are reported by the compiler */
#define TB_COMPILE_TIME_ASSERT_TAG(exp,tag)	TB_COMPILE_TIME_ASSERT_impl((exp), tag)
/* implementation helper */
#define TB_COMPILE_TIME_ASSERT_impl(exp,tag) extern char __tb_compile_time_assert_##tag [1 - 2*!(exp)]
#endif  // TB_COMPILE_TIME_ASSERT

#endif // _lint


/* compile time check of type */
#ifdef _lint
/* don't confuse lint with this special stuff */
/*lint -emacro( {19}, TB_CHECK_SIZEOF) */
#define TB_CHECK_SIZEOF(type,size)
#else

#ifndef TB_CHECK_SIZEOF
#define TB_CHECK_SIZEOF(type,size)	TB_COMPILE_TIME_ASSERT(sizeof(type)==(size))
#endif

#endif // _lint



#endif  /* __tbase_platform_h__ */

/*************************** EOF **************************************/
