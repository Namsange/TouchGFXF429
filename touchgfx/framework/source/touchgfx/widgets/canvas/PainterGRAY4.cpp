/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/canvas/PainterGRAY4.hpp>
#include <touchgfx/Color.hpp>
#include <platform/driver/lcd/LCD4bpp.hpp>

namespace touchgfx
{

PainterGRAY4::PainterGRAY4(colortype color, uint8_t alpha) :
    AbstractPainterGRAY4()
{
    setColor(color, alpha);
}

void PainterGRAY4::setColor(colortype color, uint8_t alpha)
{
    painterGray = (uint8_t)color & 0x0F;
    painterAlpha = alpha;
}

touchgfx::colortype PainterGRAY4::getColor() const
{
    return static_cast<colortype>(painterGray);
}

void PainterGRAY4::setAlpha(uint8_t alpha)
{
    painterAlpha = alpha;
}

uint8_t PainterGRAY4::getAlpha() const
{
    return painterAlpha;
}

void PainterGRAY4::render(uint8_t* ptr, int x, int xAdjust, int y, unsigned count, const uint8_t* covers)
{
    currentX = x + areaOffsetX;
    currentY = y + areaOffsetY;
    x += xAdjust;
    uint8_t totalAlpha = (widgetAlpha * painterAlpha) / 255;
    if (totalAlpha == 255)
    {
        do
        {
            uint8_t alpha = *covers;
            covers++;
            if (alpha == 255) // max alpha=255 on "*covers" and max alpha=255 on "widgetAlpha"
            {
                // Render a solid pixel
                LCD4setPixel(ptr, x, painterGray);
            }
            else
            {
                uint8_t p_gray = LCD4getPixel(ptr, x);
                LCD4setPixel(ptr, x, static_cast<uint8_t>((((painterGray - p_gray) * alpha) >> 8) + p_gray));
            }
            currentX++;
            x++;
        }
        while (--count != 0);
    }
    else if (totalAlpha != 0)
    {
        do
        {
            uint16_t alpha = (*covers) * totalAlpha;
            covers++;
            uint8_t p_gray = LCD4getPixel(ptr, x);
            LCD4setPixel(ptr, x, static_cast<uint8_t>((((painterGray - p_gray) * alpha) >> 16) + p_gray));
            currentX++;
            x++;
        }
        while (--count != 0);
    }
}

bool PainterGRAY4::renderNext(uint8_t& gray, uint8_t& alpha)
{
    gray = painterGray;
    alpha = painterAlpha;
    return true;
}

} // namespace touchgfx
