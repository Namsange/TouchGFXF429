/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/containers/progress_indicators/LineProgress.hpp>

namespace touchgfx
{

LineProgress::LineProgress()
    : AbstractProgressIndicator(), line(), endX(0), endY(0)
{
    progressIndicatorContainer.add(line);
    line.setPosition(0, 0, getWidth(), getHeight());
}

LineProgress::~LineProgress()
{
}

void LineProgress::setProgressIndicatorPosition(int16_t x, int16_t y, int16_t width, int16_t height)
{
    line.setPosition(0, 0, width, height);

    AbstractProgressIndicator::setProgressIndicatorPosition(x, y, width, height);
}

void LineProgress::setPainter(AbstractPainter& painter)
{
    line.setPainter(painter);
}

void LineProgress::setStart(int x, int y)
{
    startX = CWRUtil::toQ5(x);
    startY = CWRUtil::toQ5(y);
    line.setStart(x, y);
}

void LineProgress::getStart(int& x, int& y) const
{
    x = startX.to<int>();
    y = startY.to<int>();
}

void LineProgress::setEnd(int x, int y)
{
    endX = CWRUtil::toQ5(x);
    endY = CWRUtil::toQ5(y);
}

void LineProgress::getEnd(int& x, int& y) const
{
    x = endX.to<int>();
    y = endY.to<int>();
}

void LineProgress::setLineWidth(int width)
{
    line.setLineWidth(width);
}

int LineProgress::getLineWidth() const
{
    int width;
    line.getLineWidth(width);
    return width;
}

void LineProgress::setLineEndingStyle(Line::LINE_ENDING_STYLE lineEndingStyle)
{
    line.setLineEndingStyle(lineEndingStyle);
}

touchgfx::Line::LINE_ENDING_STYLE LineProgress::getLineEndingStyle() const
{
    return line.getLineEndingStyle();
}

void LineProgress::setAlpha(uint8_t alpha)
{
    line.setAlpha(alpha);
}

uint8_t LineProgress::getAlpha() const
{
    return line.getAlpha();
}

void LineProgress::setValue(int value)
{
    if (rangeSteps > 0)
    {
        AbstractProgressIndicator::setValue(value);
        int progress = (int)AbstractProgressIndicator::getProgress(rangeSteps);
        CWRUtil::Q5 x = startX + (endX - startX) / (int)rangeSteps * progress;
        CWRUtil::Q5 y = startY + (endY - startY) / (int)rangeSteps * progress;
        line.updateEnd(x, y);
    }
}

}
