/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef BUTTONS_HPP
#define BUTTONS_HPP

namespace touchgfx
{
/**
 * @class Buttons Buttons.hpp touchgfx/hal/Buttons.hpp
 *
 * @brief A buttons.
 */
class Buttons
{
public:

    /**
     * @fn static void Buttons::init();
     *
     * @brief Perform configuration of IO pins.
     *
     *        Perform configuration of IO pins.
     */
    static void init();

    /**
     * @fn static unsigned int Buttons::sample();
     *
     * @brief Sample button states.
     *
     *        Sample button states.
     *
     * @return the sampled state of the buttons.
     */
    static unsigned int sample();

};
}
#endif // BUTTONS_HPP
