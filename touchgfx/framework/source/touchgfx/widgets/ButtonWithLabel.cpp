/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/FontManager.hpp>

namespace touchgfx
{

ButtonWithLabel::ButtonWithLabel()
    : Button(), color(0), colorPressed(0), rotation(TEXT_ROTATE_0), textHeightIncludingSpacing(0)
{
}

void ButtonWithLabel::draw(const Rect& area) const
{
    Button::draw(area);

    const Font* fontToDraw = typedText.getFont();
    if ((fontToDraw != 0) && typedText.hasValidId())
    {
        uint8_t height = textHeightIncludingSpacing;
        int16_t offset;
        Rect labelRect;
        switch (rotation)
        {
        default:
        case TEXT_ROTATE_0:
        case TEXT_ROTATE_180:
            offset = (this->getHeight() - height) / 2;
            labelRect = Rect(0, offset, this->getWidth(), height);
            break;
        case TEXT_ROTATE_90:
        case TEXT_ROTATE_270:
            offset = (this->getWidth() - height) / 2;
            labelRect = Rect(offset, 0, height, this->getHeight());
            break;
        }
        Rect dirty = labelRect & area;

        if (!dirty.isEmpty())
        {
            dirty.x -= labelRect.x;
            dirty.y -= labelRect.y;
            translateRectToAbsolute(labelRect);
            LCD::StringVisuals visuals(fontToDraw, pressed ? colorPressed : color, alpha, typedText.getAlignment(), 0, rotation, typedText.getTextDirection(), 0, WIDE_TEXT_NONE);
            HAL::lcd().drawString(labelRect, dirty, visuals, typedText.getText());
        }
    }
}

} // namespace touchgfx
