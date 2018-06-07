/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/canvas/PainterBW.hpp>

namespace touchgfx
{

unsigned PainterBW::bw(unsigned red, unsigned green, unsigned blue)
{
    return (red * 77 + green * 150 + blue * 29) >> 15;
}

void PainterBW::setColor(colortype color)
{
    painterColor = color ? 1 : 0;
}

touchgfx::colortype PainterBW::getColor() const
{
    return static_cast<colortype>(painterColor);
}

void PainterBW::render(uint8_t* ptr, int x, int xAdjust, int y, unsigned count, const uint8_t* covers)
{
    (void)covers; // Unused

    currentX = x + areaOffsetX;
    currentY = y + areaOffsetY;
    x += xAdjust;
    unsigned char* p = ptr + (x / 8);

    do
    {
        unsigned pixel = painterColor << (7 - (x % 8));
        if (!painterColor)
        {
            *p &= ~pixel;
        }
        else
        {
            *p |= pixel;
        }
        if (((++x) % 8) == 0)
        {
            p++;
        }
        currentX++;
    }
    while (--count);
}

bool PainterBW::renderNext(uint8_t& color)
{
    color = painterColor;
    return true;
}

} // namespace touchgfx
