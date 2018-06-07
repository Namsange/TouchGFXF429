/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <platform/driver/touch/SDL2TouchController.hpp>
#include <platform/hal/simulator/sdl2/HALSDL2.hpp>

namespace touchgfx
{

void touchgfx::SDL2TouchController::init()
{
}

bool touchgfx::SDL2TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    return static_cast<HALSDL2*>(HAL::getInstance())->doSampleTouch(x, y); //lint !e1774
}

}
