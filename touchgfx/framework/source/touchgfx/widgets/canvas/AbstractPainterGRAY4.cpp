/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/canvas/AbstractPainterGRAY4.hpp>
#include <touchgfx/Color.hpp>
#include <platform/driver/lcd/LCD4bpp.hpp>

namespace touchgfx
{

void AbstractPainterGRAY4::render(uint8_t* ptr,
                                  int x,
                                  int xAdjust,
                                  int y,
                                  unsigned count,
                                  const uint8_t* covers)
{
    currentX = x + areaOffsetX;
    currentY = y + areaOffsetY;
    x += xAdjust;
    if (renderInit())
    {
        do
        {
            uint8_t gray, alpha;
            if (renderNext(gray, alpha))
            {
                if (widgetAlpha < 255)
                {
                    alpha = static_cast<uint8_t>((alpha * widgetAlpha) / 255);
                }
                uint32_t combinedAlpha = ((*covers) * alpha) / 255;
                covers++;

                if (combinedAlpha == 255) // max alpha=255 on "*covers" and max alpha=255 on "widgetAlpha"
                {
                    // Render a solid pixel
                    renderPixel(ptr, x, gray);
                }
                else
                {
                    uint8_t p_gray = LCD4getPixel(ptr, x);
                    uint16_t ialpha = 0x100 - combinedAlpha;
                    renderPixel(ptr, x, static_cast<uint8_t>((p_gray * ialpha + gray * combinedAlpha) >> 8));
                }
            }
            currentX++;
            x++;
        }
        while (--count != 0);
    }
}

void AbstractPainterGRAY4::renderPixel(uint8_t* p, uint16_t offset, uint8_t gray)
{
    LCD4setPixel(p, offset, gray & 0x0F);
}

} // namespace touchgfx
