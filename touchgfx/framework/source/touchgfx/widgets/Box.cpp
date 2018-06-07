/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/Box.hpp>

namespace touchgfx
{

Rect Box::getSolidRect() const
{
    Rect solidRect(0, 0, 0, 0);
    if (reportAsSolid || alpha == 255)
    {
        solidRect.width = rect.width;
        solidRect.height = rect.height;
    }
    return solidRect;
}

void Box::draw(const Rect& area) const
{
    Rect dirty = area;
    translateRectToAbsolute(dirty);
    HAL::lcd().fillRect(dirty, color, alpha);
}

} // namespace touchgfx
