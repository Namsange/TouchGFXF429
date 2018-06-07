/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/containers/clock/AbstractClock.hpp>

namespace touchgfx
{

AbstractClock::AbstractClock() :
    Container(),
    currentHour(0),
    currentMinute(0),
    currentSecond(0)
{

}

void AbstractClock::setTime24Hour(uint8_t hour, uint8_t minute, uint8_t second)
{
    currentHour = hour % 24;
    currentMinute = minute % 60;
    currentSecond = second % 60;

    updateClock();
}

void AbstractClock::setTime12Hour(uint8_t hour, uint8_t minute, uint8_t second, bool am)
{
    setTime24Hour((hour % 12) + (am ? 0 : 12), minute, second);
}

uint8_t AbstractClock::getCurrentHour() const
{
    return currentHour;
}

uint8_t AbstractClock::getCurrentMinute() const
{
    return currentMinute;
}

uint8_t AbstractClock::getCurrentSecond() const
{
    return currentSecond;
}

}
