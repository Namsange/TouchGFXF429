/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/Color.hpp>

namespace touchgfx
{

PainterRGB888::PainterRGB888(colortype color, uint8_t alpha) :
    AbstractPainterRGB888()
{
    setColor(color, alpha);
}

void PainterRGB888::setColor(colortype color, uint8_t alpha)
{
    painterRed   = Color::getRedColor(color);
    painterGreen = Color::getGreenColor(color);
    painterBlue  = Color::getBlueColor(color);
    painterAlpha = alpha;
}

touchgfx::colortype PainterRGB888::getColor() const
{
    return Color::getColorFrom24BitRGB(painterRed, painterGreen, painterBlue);
}

void PainterRGB888::setAlpha(uint8_t alpha)
{
    painterAlpha = alpha;
}

uint8_t PainterRGB888::getAlpha() const
{
    return painterAlpha;
}

void PainterRGB888::render(uint8_t* ptr, int x, int xAdjust, int y, unsigned count, const uint8_t* covers)
{
    uint8_t* p = reinterpret_cast<uint8_t*>(ptr) + ((x + xAdjust) * 3);
    uint8_t pByte;
    uint8_t totalAlpha = (widgetAlpha * painterAlpha) / 255;
    if (totalAlpha == 255)
    {
        do
        {
            uint32_t alpha = *covers++;
            if (alpha == 255)
            {
                *p++ = painterBlue;
                *p++ = painterGreen;
                *p++ = painterRed;
            }
            else
            {
                pByte = *p;
                *p++ = static_cast<uint8_t>((((painterBlue  - pByte) * alpha) >> 8) + pByte);
                pByte = *p;
                *p++ = static_cast<uint8_t>((((painterGreen - pByte) * alpha) >> 8) + pByte);
                pByte = *p;
                *p++ = static_cast<uint8_t>((((painterRed   - pByte) * alpha) >> 8) + pByte);
            }
        }
        while (--count != 0);
    }
    else if (totalAlpha != 0)
    {
        do
        {
            uint32_t alpha = *covers++ * totalAlpha; // never 0 as both are !=0
            pByte = *p;
            *p++ = static_cast<uint8_t>((((painterBlue - pByte) * alpha) >> 16) + pByte);
            pByte = *p;
            *p++ = static_cast<uint8_t>((((painterGreen - pByte) * alpha) >> 16) + pByte);
            pByte = *p;
            *p++ = static_cast<uint8_t>((((painterRed - pByte) * alpha) >> 16) + pByte);
        }
        while (--count != 0);
    }
}

bool PainterRGB888::renderNext(uint8_t& red, uint8_t& green, uint8_t& blue, uint8_t& alpha)
{
    red   = painterRed;
    green = painterGreen;
    blue  = painterBlue;
    alpha = painterAlpha;
    return true;
}

} // namespace touchgfx
