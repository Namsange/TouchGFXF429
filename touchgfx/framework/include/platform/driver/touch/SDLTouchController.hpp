/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef SDLTOUCHCONTROLLER_HPP
#define SDLTOUCHCONTROLLER_HPP

#include <platform/driver/touch/TouchController.hpp>

namespace touchgfx
{
/**
 * @class SDLTouchController SDLTouchController.hpp platform/driver/touch/SDLTouchController.hpp
 *
 * @brief TouchController for the simulator.
 *
 *        TouchController for the simulator.
 *
 * @sa TouchController
 */
class SDLTouchController : public TouchController
{
public:
    /**
     * @fn virtual void SDLTouchController::init();
     *
     * @brief Initializes touch controller.
     *
     *        Initializes touch controller.
     */
    virtual void init();

    /**
     * @fn virtual bool SDLTouchController::sampleTouch(int32_t& x, int32_t& y);
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
    virtual bool sampleTouch(int32_t& x, int32_t& y);
};

} // namespace touchgfx

#endif // SDLTOUCHCONTROLLER_HPP
