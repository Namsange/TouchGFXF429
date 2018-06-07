/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/ButtonWithIcon.hpp>

namespace touchgfx
{

ButtonWithIcon::ButtonWithIcon() :
    Button(),
    iconX(0),
    iconY(0)
{
}

void ButtonWithIcon::setBitmaps(const Bitmap& newBackgroundReleased, const Bitmap& newBackgroundPressed,
                                const Bitmap& newIconReleased,       const Bitmap& newIconPressed)
{
    Button::setBitmaps(newBackgroundReleased, newBackgroundPressed);

    iconReleased = newIconReleased;
    iconPressed = newIconPressed;

    iconX = (getWidth() / 2) - (newIconPressed.getWidth() / 2);
    iconY = (getHeight() / 2) - (newIconPressed.getHeight() / 2);
}

void ButtonWithIcon::draw(const Rect& invalidatedArea) const
{
    Button::draw(invalidatedArea);

    Bitmap bmp((pressed ? iconPressed : iconReleased));
    Rect iconRect(iconX, iconY, bmp.getWidth(), bmp.getHeight());
    Rect dirty = invalidatedArea & iconRect;
    if ((bmp.getId() != BITMAP_INVALID) && !dirty.isEmpty())
    {
        Rect r;
        translateRectToAbsolute(r);
        dirty.x -= iconX;
        dirty.y -= iconY;
        HAL::lcd().drawPartialBitmap(bmp, r.x + iconX, r.y + iconY, dirty, alpha);
    }
}

} // namespace touchgfx
