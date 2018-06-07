/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef ATOMIC_HPP
#define ATOMIC_HPP

/**
 * Defines a atomic write on suported platforms
 */

#if defined(WIN32)

#include <windows.h>
typedef LONG atomic_t;

/**
 * @fn inline void atomic_set(atomic_t& target, atomic_t value)
 *
 * @brief Makes a atomic write of value to target.
 *
 *        Makes a atomic write of value to target.
 *
 * @param [out] target The value to write to.
 * @param value        The value to write.
 */
inline void atomic_set(atomic_t& target, atomic_t value)
{
    InterlockedExchange(&target, value);
}

#elif defined(__GNUC__)

#include <csignal>
typedef sig_atomic_t atomic_t;

/**
 * @fn inline void atomic_set(atomic_t& target, atomic_t value)
 *
 * @brief Makes a atomic write of value to target.
 *
 *        Makes a atomic write of value to target.
 *
 * @param [out] target The value to write to.
 * @param value        The value to write.
 */
inline void atomic_set(atomic_t& target, atomic_t value)
{
    __sync_synchronize();
    target = value;
}

#elif defined(__IAR_SYSTEMS_ICC__)

typedef unsigned long atomic_t;

/**
 * @fn inline void atomic_set(atomic_t& target, atomic_t value)
 *
 * @brief Makes a atomic write of value to target.
 *
 *        Makes a atomic write of value to target.
 *
 * @note Assume that 32 bit writes are atomic.
 *
 * @param [out] target The value to write to.
 * @param value        The value to write.
 */
inline void atomic_set(atomic_t& target, atomic_t value)
{
    target = value;
}
#elif defined(__ARMCC_VERSION)

typedef unsigned long atomic_t;

/**
 * @fn inline void atomic_set(atomic_t& target, atomic_t value)
 *
 * @brief Makes a atomic write of value to target.
 *
 *        Makes a atomic write of value to target.
 *
 * @param [out] target The value to write to.
 * @param value        The value to write.
 */
inline void atomic_set(atomic_t& target, atomic_t value)
{
    target = value;
}
#else

#error "Compiler/platform not supported"

#endif

#endif // ATOMIC_HPP
