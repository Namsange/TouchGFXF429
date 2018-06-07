/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef NOTOUCHCONTROLLER_HPP
#define NOTOUCHCONTROLLER_HPP

#include <platform/driver/touch/TouchController.hpp>

namespace touchgfx
{
/**
 * Empty TouchController implementation which does nothing. Use this if your display does
 * not have touch input capabilities.
 */
class NoTouchController : public TouchController
{
public:
    /**
     * @fn virtual void NoTouchController::init()
     *
     * @brief Empty initialization.
     *
     *        Empty initialization.
     */
    virtual void init()
    {
    }

    /**
     * @fn virtual NoTouchController::~NoTouchController()
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~NoTouchController()
    {
    }

    /**
     * @fn virtual bool NoTouchController::sampleTouch(int32_t& x, int32_t& y)
     *
     * @brief Does nothing.
     *
     * @param [out] x unused.
     * @param [out] y unused.
     *
     * @return false.
     */
    virtual bool sampleTouch(int32_t& x, int32_t& y)
    {
        return false;
    }
};

} // namespace touchgfx

#endif // NOTOUCHCONTROLLER_HPP
