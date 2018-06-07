/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef BOARDCONFIGURATION_HPP
#define BOARDCONFIGURATION_HPP

namespace touchgfx
{
/**
 * @fn void hw_init();
 *
 * @brief Function to perform generic hardware initialization of the board.
 *
 *        Function to perform generic hardware initialization of the board. This function
 *        prototype is only provided as a convention.
 */
void hw_init();

/**
 * @fn void touchgfx_init();
 *
 * @brief Function to perform touchgfx initialization.
 *
 *        Function to perform touchgfx initialization. This function prototype is only provided
 *        as a convention.
 */
void touchgfx_init();

} // namespace touchgfx

#endif // BOARDCONFIGURATION_HPP
