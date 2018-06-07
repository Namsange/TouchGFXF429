/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef UTILS_HPP
#define UTILS_HPP

#ifdef SIMULATOR
#include <stdarg.h>
#ifndef __linux__
#include <windows.h>
#endif
#include <stdio.h>
#endif
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/Bitmap.hpp>

#if defined(SIMULATOR) && !defined(__linux__)

/**
 * @fn void touchgfx_enable_stdio();
 *
 * @brief Ensure there is a console window to print to and read from.
 *
 *        Ensure there is a console window to print to using printf() or std::cout, and read
 *        from using e.g. fgets or std::cin. Alternatively, instead of using printf(), simply
 *        use touchgfx_printf() which will ensure there is a console to write to. After the
 *        first call to touchgfx_printf, it will also be possible to read from stdin.
 *
 * @see touchgfx_printf
 */
void touchgfx_enable_stdio();
#else
#define touchgfx_enable_stdio()
#endif

#ifdef SIMULATOR

/**
 * @fn void touchgfx_printf(const char* format, ...);
 *
 * @brief TouchGFX printf.
 *
 *        TouchGFX printf that will only work on simulators. On Windows systems, a new console
 *        window will be created where the output is printed, on Linux systems, output will be
 *        sent to /var/log/syslog. For target systems, calls to touchgfx_printf() will be
 *        removed and not cause any use of memory.
 *        Unlike printf(), touchfgx_printf() does not return number of characters written.
 *
 * @param format Describes the format to use, see printf().
 * @param ...    Variable arguments providing additional information.
 *
 * @see touchgfx_enable_stdio
 */
void touchgfx_printf(const char* format, ...);
#else
#define touchgfx_printf(format, ...)
#endif

namespace touchgfx
{
/**
 * Provides utility functions.
 */

/**
 * @fn void memset(void* data, uint8_t c, uint32_t size);
 *
 * @brief Simple implementation of the standard memset function.
 *
 *        Simple implementation of the standard memset function.
 *
 * @param [out] data Address of data to set.
 * @param       c    Value to set.
 * @param       size Number of bytes to set.
 */
void memset(void* data, uint8_t c, uint32_t size);

/**
 * @fn RenderingVariant lookupNearestNeighborRenderVariant(const Bitmap& bitmap);
 *
 * @brief Returns the associated nearest neighbor render variant based on the bitmap format.
 *
 *        Returns the associated nearest neighbor render variant based on the bitmap format.
 *
 * @param bitmap The bitmap.
 *
 * @return A RenderingVariant based on the bitmap format.
 */
RenderingVariant lookupNearestNeighborRenderVariant(const Bitmap& bitmap);

/**
 * @fn RenderingVariant lookupBilinearRenderVariant(const Bitmap& bitmap);
 *
 * @brief Returns the associated bilinear render variant based on the bitmap format.
 *
 *        Returns the associated bilinear render variant based on the bitmap format.
 *
 * @param bitmap The bitmap.
 *
 * @return A RenderingVariant based on the bitmap format.
 */
RenderingVariant lookupBilinearRenderVariant(const Bitmap& bitmap);

/**
 * @fn template <class T> T abs(T d)
 *
 * @brief Simple implementation of the standard abs function
 *
 *        Simple implementation of the standard abs function.
 *
 * @tparam T The class type on which to perform the abs.
 * @param d The entity on which to perform the abs.
 *
 * @return The absolute (non-negative) value of d.
 */
template <class T>
T abs(T d)
{
    if (d < 0)
    {
        return -d;
    }
    return d;
}

} // namespace touchgfx

#endif // UTILS_HPP
