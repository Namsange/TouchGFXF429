/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/AbstractButton.hpp>

namespace touchgfx
{

void AbstractButton::handleClickEvent(const ClickEvent& event)
{
    bool wasPressed = pressed;
    pressed = (event.getType() == ClickEvent::PRESSED);
    if ((pressed && !wasPressed) || (!pressed && wasPressed))
    {
        // Pressed state changed, so invalidate
        invalidate();
    }
    if (wasPressed && (event.getType() == ClickEvent::RELEASED) && action)
    {
        // This is a click. Fire callback.
        if (action->isValid())
        {
            action->execute(*this);
        }
    }
}

} // namespace touchgfx
