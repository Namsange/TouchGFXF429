/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/canvas/AbstractPainterRGB565.hpp>
#include <touchgfx/Color.hpp>

namespace touchgfx
{

void AbstractPainterRGB565::render(uint8_t* ptr,
                                   int x,
                                   int xAdjust,
                                   int y,
                                   unsigned count,
                                   const uint8_t* covers)
{
    uint16_t* p = reinterpret_cast<uint16_t*>(ptr) + (x + xAdjust);

    currentX = x + areaOffsetX;
    currentY = y + areaOffsetY;
    if (renderInit())
    {
        do
        {
            uint8_t red, green, blue, alpha;
            if (renderNext(red, green, blue, alpha))
            {
                if (widgetAlpha < 255)
                {
                    alpha = static_cast<uint8_t>((alpha * widgetAlpha) / 255);
                }
                uint32_t combinedAlpha = (*covers) * alpha;
                covers++;

                if (combinedAlpha == (255u * 255u)) // max alpha=255 on "*covers" and max alpha=255 on "widgetAlpha"
                {
                    // Render a solid pixel
                    renderPixel(p, red, green, blue);
                }
                else
                {
                    uint8_t p_red = (*p & 0xF800) >> 8;
                    p_red |= p_red >> 5;
                    uint8_t p_green = (*p & 0x07E0) >> 3;
                    p_green |= p_green >> 6;
                    uint8_t p_blue = (*p & 0x001F) << 3;
                    p_blue |= p_blue >> 5;
                    renderPixel(p,
                                static_cast<uint8_t>((((red   - p_red)   * combinedAlpha) + (p_red   << 16)) >> 16),
                                static_cast<uint8_t>((((green - p_green) * combinedAlpha) + (p_green << 16)) >> 16),
                                static_cast<uint8_t>((((blue  - p_blue)  * combinedAlpha) + (p_blue  << 16)) >> 16));
                }
            }
            p++;
            currentX++;
        }
        while (--count != 0);
    }
}

void AbstractPainterRGB565::renderPixel(uint16_t* p, uint8_t red, uint8_t green, uint8_t blue)
{
    *p = ((red << 8) & RMASK) | ((green << 3) & GMASK) | ((blue >> 3) & BMASK);
}

} // namespace touchgfx
