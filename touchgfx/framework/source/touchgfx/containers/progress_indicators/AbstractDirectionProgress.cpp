/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/containers/progress_indicators/AbstractDirectionProgress.hpp>

namespace touchgfx
{

AbstractDirectionProgress::AbstractDirectionProgress()
    : AbstractProgressIndicator()
{
    AbstractDirectionProgress::setDirection(RIGHT);
}

AbstractDirectionProgress::~AbstractDirectionProgress()
{
}

void AbstractDirectionProgress::setDirection(DirectionType direction)
{
    progressDirection = direction;
    setValue(getValue());
}

touchgfx::AbstractDirectionProgress::DirectionType AbstractDirectionProgress::getDirection() const
{
    return progressDirection;
}

}
