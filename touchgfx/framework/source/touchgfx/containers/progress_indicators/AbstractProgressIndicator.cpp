/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/containers/progress_indicators/AbstractProgressIndicator.hpp>

namespace touchgfx
{

AbstractProgressIndicator::AbstractProgressIndicator()
    : Container(), rangeMin(0), rangeMax(100), currentValue(0), rangeSteps(100), rangeStepsMin(0)
{
    background.setXY(0, 0);
    Container::add(background);

    Container::add(progressIndicatorContainer);
}

touchgfx::AbstractProgressIndicator::~AbstractProgressIndicator()
{
}

void AbstractProgressIndicator::setBackground(const Bitmap& bmpBackground)
{
    background.setBitmap(bmpBackground);
    Drawable::setWidth(background.getWidth());
    Drawable::setHeight(background.getHeight());
}

void AbstractProgressIndicator::setProgressIndicatorPosition(int16_t x, int16_t y, int16_t width, int16_t height)
{
    progressIndicatorContainer.setPosition(x, y, width, height);

    if (getWidth() < x + width)
    {
        AbstractProgressIndicator::setWidth(x + width);
    }

    if (getHeight() < y + height)
    {
        AbstractProgressIndicator::setHeight(y + height);
    }
}

int16_t AbstractProgressIndicator::getProgressIndicatorX() const
{
    return progressIndicatorContainer.getX();
}

int16_t AbstractProgressIndicator::getProgressIndicatorY() const
{
    return progressIndicatorContainer.getY();
}

int16_t AbstractProgressIndicator::getProgressIndicatorWidth() const
{
    return progressIndicatorContainer.getWidth();
}

int16_t AbstractProgressIndicator::getProgressIndicatorHeight() const
{
    return progressIndicatorContainer.getHeight();
}

void AbstractProgressIndicator::setRange(int16_t min, int16_t max, uint16_t steps /*= 0*/, uint16_t minStep /*= 0*/)
{
    assert(min < max);
    rangeMin = min;
    rangeMax = max;
    setValue(currentValue);
    if (steps == 0)
    {
        rangeSteps = max - min;
    }
    else
    {
        rangeSteps = steps;
    }
    rangeStepsMin = minStep;
    assert(rangeStepsMin < rangeSteps);
}

void AbstractProgressIndicator::getRange(int16_t& min, int16_t& max, uint16_t& steps, uint16_t& minStep) const
{
    min = rangeMin;
    max = rangeMax;
    steps = rangeSteps;
    minStep = rangeStepsMin;
}

void AbstractProgressIndicator::getRange(int16_t& min, int16_t& max, uint16_t& steps) const
{
    min = rangeMin;
    max = rangeMax;
    steps = rangeSteps;
}

void AbstractProgressIndicator::getRange(int16_t& min, int16_t& max) const
{
    min = rangeMin;
    max = rangeMax;
}

void AbstractProgressIndicator::setValue(int value)
{
    int newValue = MAX(value, rangeMin);
    newValue = MIN(newValue, rangeMax);
    currentValue = newValue;
}

int AbstractProgressIndicator::getValue() const
{
    return currentValue;
}

uint16_t AbstractProgressIndicator::getProgress(uint16_t range /*= 100*/) const
{
    if (range == 0)
    {
        return 0;
    }
    uint16_t progress = ((currentValue - rangeMin) * range) / (rangeMax - rangeMin);
    // Calculate range/rangeSteps as "intpart+fracpart/rangeSteps"
    uint16_t intpart = range / rangeSteps;
    uint16_t fracpart = range % rangeSteps;
    // Now "progress/(intpart+fracpart/rangeSteps)" = "(progress*rangeSteps)/(intpart*rangeSteps+fracpart)"
    uint16_t count = rangeStepsMin + (progress * (rangeSteps - rangeStepsMin)) / range;
    return (count * intpart + (count * fracpart) / rangeSteps);
}

}
