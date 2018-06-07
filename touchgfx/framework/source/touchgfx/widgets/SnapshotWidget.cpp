/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/SnapshotWidget.hpp>

namespace touchgfx
{

SnapshotWidget::SnapshotWidget() : Widget(), fbCopy(0), alpha(255)
{
}

SnapshotWidget::~SnapshotWidget()
{
}

void SnapshotWidget::draw(const Rect& invalidatedArea) const
{
    if (!fbCopy)
    {
        return;
    }

    Rect absRect;
    translateRectToAbsolute(absRect);
    absRect.width = rect.width;
    absRect.height = rect.height;
    HAL::lcd().blitCopy(fbCopy, absRect, invalidatedArea, alpha, false);
}

Rect SnapshotWidget::getSolidRect() const
{
    if (alpha < 255)
    {
        return Rect(0, 0, 0, 0);
    }

    return Rect(0, 0, getWidth(), getHeight());
}

void SnapshotWidget::makeSnapshot()
{
    fbCopy = reinterpret_cast<uint16_t*>(HAL::lcd().copyFrameBufferRegionToMemory(rect));
}

} // namespace touchgfx
