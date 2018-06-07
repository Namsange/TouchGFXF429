/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef CONFIG_HPP
#define CONFIG_HPP

/**
 * Section placements of external flash data.
 */
#ifdef SIMULATOR
#define LOCATION_EXTFLASH_PRAGMA
#define LOCATION_EXTFLASH_ATTRIBUTE
#else
#ifdef __GNUC__
#ifdef __CODE_RED
#include <cr_section_macros.h>
#define LOCATION_EXTFLASH_PRAGMA
#define LOCATION_EXTFLASH_ATTRIBUTE __RODATA(SPIFI)
#else
#define LOCATION_EXTFLASH_PRAGMA
#define LOCATION_EXTFLASH_ATTRIBUTE __attribute__ ((section ("ExtFlashSection"))) __attribute__ ((aligned(4)))
#endif
#elif defined __ICCARM__
#define LOCATION_EXTFLASH_PRAGMA _Pragma("location=\"ExtFlashSection\"")
#define LOCATION_EXTFLASH_ATTRIBUTE
#elif defined(__ARMCC_VERSION)
#define LOCATION_EXTFLASH_PRAGMA
#define LOCATION_EXTFLASH_ATTRIBUTE __attribute__ ((section ("ExtFlashSection"))) __attribute__ ((aligned(4)))
#endif
#endif

#ifdef SIMULATOR
#define FONT_LOCATION_FLASH_PRAGMA
#define FONT_LOCATION_FLASH_ATTRIBUTE
#else
#ifdef __GNUC__
#ifdef __CODE_RED
#include <cr_section_macros.h>
#define FONT_LOCATION_FLASH_PRAGMA
#define FONT_LOCATION_FLASH_ATTRIBUTE __RODATA(SPIFI)
#else
#define FONT_LOCATION_FLASH_PRAGMA
#define FONT_LOCATION_FLASH_ATTRIBUTE __attribute__ ((section ("FontFlashSection"))) __attribute__ ((aligned(4)))
#endif
#elif defined __ICCARM__
#define FONT_LOCATION_FLASH_PRAGMA _Pragma("location=\"FontFlashSection\"")
#define FONT_LOCATION_FLASH_ATTRIBUTE
#elif defined(__ARMCC_VERSION)
#define FONT_LOCATION_FLASH_PRAGMA
#define FONT_LOCATION_FLASH_ATTRIBUTE __attribute__ ((section ("FontFlashSection"))) __attribute__ ((aligned(4)))
#endif
#endif

#ifdef SIMULATOR
#define TEXT_LOCATION_FLASH_PRAGMA
#define TEXT_LOCATION_FLASH_ATTRIBUTE
#else
#ifdef __GNUC__
#ifdef __CODE_RED
#include <cr_section_macros.h>
#define TEXT_LOCATION_FLASH_PRAGMA
#define TEXT_LOCATION_FLASH_ATTRIBUTE __RODATA(SPIFI)
#else
#define TEXT_LOCATION_FLASH_PRAGMA
#define TEXT_LOCATION_FLASH_ATTRIBUTE __attribute__ ((section ("TextFlashSection"))) __attribute__ ((aligned(4)))
#endif
#elif defined __ICCARM__
#define TEXT_LOCATION_FLASH_PRAGMA _Pragma("location=\"TextFlashSection\"")
#define TEXT_LOCATION_FLASH_ATTRIBUTE
#elif defined(__ARMCC_VERSION)
#define TEXT_LOCATION_FLASH_PRAGMA
#define TEXT_LOCATION_FLASH_ATTRIBUTE __attribute__ ((section ("TextFlashSection"))) __attribute__ ((aligned(4)))
#endif
#endif

/**
 * To force inline of time critical functions
 */
#ifdef SIMULATOR
#define FORCE_INLINE_FUNCTION inline
#else
#ifdef __GNUC__
#ifdef __CODE_RED
#define FORCE_INLINE_FUNCTION inline
#else
#define FORCE_INLINE_FUNCTION __attribute__((always_inline)) inline
#endif
#elif defined __ICCARM__
#define FORCE_INLINE_FUNCTION _Pragma("inline=forced")
#elif defined(__ARMCC_VERSION)
#define FORCE_INLINE_FUNCTION __forceinline
#endif
#endif



/**
 * To be able to use __restrict__ on the supported platform. The IAR compiler does not support this
 */
#ifdef __GNUC__
#define RESTRICT __restrict__
#else
#define RESTRICT
#endif // __GNUC__

/**
 * Use KEEP to make sure the compiler does not remove this
 */
#ifdef __ICCARM__
#define KEEP __root
#else
#define KEEP
#endif

#endif // CONFIG_HPP
