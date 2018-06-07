/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/ToggleButton.hpp>

namespace touchgfx
{

ToggleButton::ToggleButton() : Button(), originalPressed(BITMAP_INVALID)
{
}

void ToggleButton::forceState(bool activeState)
{
    if (activeState)
    {
        // up should equal originalPressed
        if (up != originalPressed)
        {
            down = up;
            up = originalPressed;
        }
    }
    else
    {
        // down should equal originalPressed
        if (down != originalPressed)
        {
            up = down;
            down = originalPressed;
        }
    }
}

void ToggleButton::handleClickEvent(const ClickEvent& event)
{
    if (pressed && (event.getType() == ClickEvent::RELEASED))
    {
        Bitmap tmp = up;
        up = down;
        down = tmp;
    }
    Button::handleClickEvent(event);
}

} // namespace touchgfx
