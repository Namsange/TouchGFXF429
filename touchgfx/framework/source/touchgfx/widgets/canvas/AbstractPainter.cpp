/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/canvas/AbstractPainter.hpp>

namespace touchgfx
{

AbstractPainter::AbstractPainter() :
    areaOffsetX(0),
    areaOffsetY(0),
    widgetAlpha(255)
{
}

AbstractPainter::~AbstractPainter()
{
}

void AbstractPainter::setOffset(uint16_t offsetX, uint16_t offsetY)
{
    areaOffsetX = offsetX;
    areaOffsetY = offsetY;
}

void AbstractPainter::setWidgetAlpha(const uint8_t alpha)
{
    widgetAlpha = alpha;
}

}
