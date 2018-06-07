/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef TOUCHCONTROLLER_HPP
#define TOUCHCONTROLLER_HPP

#include <touchgfx/hal/Types.hpp>

namespace touchgfx
{
/**
 * @class TouchController TouchController.hpp platform/driver/touch/TouchController.hpp
 *
 * @brief Basic Touch Controller interface.
 *
 *        Basic Touch Controller interface.
 */
class TouchController
{
public:
    /**
     * @fn virtual TouchController::~TouchController()
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~TouchController()
    {
    }

    /**
     * @fn virtual void TouchController::init() = 0;
     *
     * @brief Initializes touch controller.
     *
     *        Initializes touch controller.
     */
    virtual void init() = 0;

    /**
     * @fn virtual bool TouchController::sampleTouch(int32_t& x, int32_t& y) = 0;
     *
     * @brief Checks whether the touch screen is being touched, and if so, what coordinates.
     *
     *        Checks whether the touch screen is being touched, and if so, what coordinates.
     *
     * @param [out] x The x position of the touch
     * @param [out] y The y position of the touch
     *
     * @return True if a touch has been detected, otherwise false.
     */
    virtual bool sampleTouch(int32_t& x, int32_t& y) = 0;
};

} // namespace touchgfx

#endif // TOUCHCONTROLLER_HPP
