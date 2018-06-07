/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/TextArea.hpp>

namespace touchgfx
{

int16_t TextArea::getTextHeight()
{
    if (typedText.hasValidId())
    {
        return getTextHeightInternal(typedText.getText());
    }
    else
    {
        return 0;
    }
}

uint16_t TextArea::getTextWidth() const
{
    return typedText.hasValidId() ? typedText.getFont()->getStringWidth(typedText.getTextDirection(), typedText.getText()) : 0;
}

void TextArea::draw(const Rect& area) const
{
    if (typedText.hasValidId())
    {
        const Font* fontToDraw = typedText.getFont();
        if (fontToDraw != 0)
        {
            LCD::StringVisuals visuals(fontToDraw, color, alpha, typedText.getAlignment(), linespace, rotation, typedText.getTextDirection(), indentation, wideTextAction);
            HAL::lcd().drawString(getAbsoluteRect(), area, visuals, typedText.getText());
        }
    }
}

void TextArea::setTypedText(TypedText t)
{
    typedText = t;
    // If this TextArea does not yet have a width and height,
    // just assign the smallest possible size to fit current text.
    if ((getWidth() == 0) && (getHeight() == 0))
    {
        resizeToCurrentText();
    }
}

void TextArea::resizeToCurrentText()
{
    if (typedText.hasValidId())
    {
        uint16_t w = getTextWidth();
        uint16_t h = getTextHeight();
        if (rotation == TEXT_ROTATE_0 || rotation == TEXT_ROTATE_180)
        {
            setWidth(w);
            setHeight(h);
        }
        else
        {
            setWidth(h);
            setHeight(w);
        }
    }
}

void TextArea::resizeHeightToCurrentText()
{
    if (typedText.hasValidId())
    {
        uint16_t h = getTextHeight();
        if (rotation == TEXT_ROTATE_0 || rotation == TEXT_ROTATE_180)
        {
            setHeight(h);
        }
        else
        {
            setWidth(h);
        }
    }
}

int16_t TextArea::getTextHeightInternal(const Unicode::UnicodeChar* format, ...) const
{
    va_list pArg;
    va_start(pArg, format);
    TextProvider textProvider;
    textProvider.initialize(format, pArg);

    int16_t numLines = HAL::lcd().getNumLines(textProvider, wideTextAction, typedText.getTextDirection(), typedText.getFont(), getWidth());

    const Font* fontToDraw = typedText.getFont();
    int16_t textHeight = fontToDraw->getMinimumTextHeight();

    va_end(pArg);
    return numLines * textHeight + (numLines - 1) * linespace;
}

} // namespace touchgfx
