/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/Color.hpp>

namespace touchgfx
{

PainterRGB565::PainterRGB565(colortype color, uint8_t alpha) :
    AbstractPainterRGB565()
{
    setColor(color, alpha);
}


void PainterRGB565::setColor(colortype color, uint8_t alpha)
{
    painterColor = (uint16_t)color;
    painterRed   = painterColor & RMASK;
    painterGreen = painterColor & GMASK;
    painterBlue  = painterColor & BMASK;
    painterAlpha = alpha;
}

touchgfx::colortype PainterRGB565::getColor() const
{
    return painterColor;
}

void PainterRGB565::setAlpha(uint8_t alpha)
{
    painterAlpha = alpha;
}

uint8_t PainterRGB565::getAlpha() const
{
    return painterAlpha;
}

void PainterRGB565::render(uint8_t* ptr, int x, int xAdjust, int y, unsigned count, const uint8_t* covers)
{
    uint16_t* p = reinterpret_cast<uint16_t*>(ptr) + (x + xAdjust);
    uint8_t totalAlpha = (widgetAlpha * painterAlpha) / 255u;
    if (totalAlpha == 255)
    {
        do
        {
            uint32_t alpha = *covers;
            covers++;
            if (alpha == 255u)
            {
                *p = painterColor;
            }
            else
            {
                *p = mixColors(painterRed, painterGreen, painterBlue, *p, alpha, 8);
            }
            p++;
        }
        while (--count != 0);
    }
    else
    {
        do
        {
            uint32_t alpha = (*covers) * totalAlpha;
            covers++;
            if (alpha == 255u * 255u)
            {
                *p = painterColor;
            }
            else
            {
                *p = mixColors(painterRed, painterGreen, painterBlue, *p, alpha, 16);
            }
            p++;
        }
        while (--count != 0);
    }
}

bool PainterRGB565::renderNext(uint8_t& red, uint8_t& green, uint8_t& blue, uint8_t& alpha)
{
    red   = painterRed >> 8;
    green = painterGreen >> 3;
    blue  = painterBlue << 3;
    alpha = painterAlpha;
    return true;
}

} // namespace touchgfx
