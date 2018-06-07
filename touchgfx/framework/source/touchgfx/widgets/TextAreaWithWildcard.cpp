/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

namespace touchgfx
{

int16_t TextAreaWithWildcardBase::calculateTextHeight(const Unicode::UnicodeChar* format, ...) const
{
    if (!typedText.hasValidId())
    {
        return 0;
    }

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
