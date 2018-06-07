/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/Button.hpp>

namespace touchgfx
{

void Button::draw(const Rect& invalidatedArea) const
{
    Bitmap bmp(AbstractButton::pressed ? down : up);
    Rect dirty(0, 0, bmp.getWidth(), bmp.getHeight());
    dirty &= invalidatedArea;
    if ((bmp.getId() != BITMAP_INVALID) && !dirty.isEmpty())
    {
        Rect r;
        translateRectToAbsolute(r);
        HAL::lcd().drawPartialBitmap(bmp, r.x, r.y, dirty, alpha);
    }
}

void Button::setBitmaps(const Bitmap& bmpReleased, const Bitmap& bmpPressed)
{
    up = bmpReleased;
    down = bmpPressed;
    // Adjust width and height of this widget to match bitmap. It is assumed
    // that the two bitmaps have same dimensions.
    Drawable::setWidth(down.getWidth());
    Drawable::setHeight(down.getHeight());
}

Rect Button::getSolidRect() const
{
    if (alpha < 255)
    {
        return Rect(0, 0, 0, 0);
    }

    return (AbstractButton::pressed ? down.getSolidRect() : up.getSolidRect());
}

} // namespace touchgfx
