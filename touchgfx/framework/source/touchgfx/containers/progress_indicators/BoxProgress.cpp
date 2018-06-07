/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/containers/progress_indicators/BoxProgress.hpp>

namespace touchgfx
{

BoxProgress::BoxProgress()
    : AbstractDirectionProgress(), box()
{
    progressIndicatorContainer.add(box);
}

BoxProgress::~BoxProgress()
{
}

void BoxProgress::setProgressIndicatorPosition(int16_t x, int16_t y, int16_t width, int16_t height)
{
    box.setPosition(0, 0, width, height);

    AbstractProgressIndicator::setProgressIndicatorPosition(x, y, width, height);
}

void BoxProgress::setColor(colortype color)
{
    box.setColor(color);
}

touchgfx::colortype BoxProgress::getColor() const
{
    return box.getColor();
}

void BoxProgress::setAlpha(uint8_t alpha)
{
    box.setAlpha(alpha);
}

uint8_t BoxProgress::getAlpha() const
{
    return box.getAlpha();
}

void BoxProgress::setValue(int value)
{
    AbstractProgressIndicator::setValue(value);
    uint16_t progress = AbstractProgressIndicator::getProgress();
    box.invalidate();
    int16_t w = (progressIndicatorContainer.getWidth() * progress) / 100;
    int16_t h = (progressIndicatorContainer.getHeight() * progress) / 100;
    switch (progressDirection)
    {
    case AbstractDirectionProgress::RIGHT:
        box.setPosition(0, 0, w, progressIndicatorContainer.getHeight());
        break;
    case AbstractDirectionProgress::LEFT:
        box.setPosition(getWidth() - w, 0, w, progressIndicatorContainer.getHeight());
        break;
    case AbstractDirectionProgress::DOWN:
        box.setPosition(0, 0, progressIndicatorContainer.getWidth(), h);
        break;
    case AbstractDirectionProgress::UP:
        box.setPosition(0, progressIndicatorContainer.getHeight() - h, progressIndicatorContainer.getWidth(), h);
        break;
    }
    box.invalidate();
}

}
