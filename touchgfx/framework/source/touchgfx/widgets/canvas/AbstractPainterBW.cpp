/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/canvas/AbstractPainterBW.hpp>

namespace touchgfx
{

void AbstractPainterBW::render(uint8_t* ptr,
                               int x,
                               int xAdjust,
                               int y,
                               unsigned count,
                               const uint8_t* covers)
{
    (void)covers; // Unused

    currentX = x + areaOffsetX;
    currentY = y + areaOffsetY;
    x += xAdjust;
    unsigned char* p = ptr + (x / 8);

    if (!renderInit())
    {
        return;
    }

    do
    {
        uint8_t color;
        if (renderNext(color))
        {
            unsigned pixel = color << (7 - (x % 8));
            if (!color)
            {
                *p &= ~pixel;
            }
            else
            {
                *p |= pixel;
            }
        }
        if (((++x) % 8) == 0)
        {
            p++;
        }
        currentX++;
    }
    while (--count);
}

} // namespace touchgfx
