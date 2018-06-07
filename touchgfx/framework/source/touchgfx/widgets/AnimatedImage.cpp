/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/widgets/AnimatedImage.hpp>

namespace touchgfx
{

void AnimatedImage::handleTickEvent()
{
    if (running)
    {
        ++ticksSinceUpdate;
        if (ticksSinceUpdate != updateTicksInterval)
        {
            return;
        }

        ticksSinceUpdate = 0;
        BitmapId currentId = getBitmap();

        if (((currentId == endId) && !reverse) || ((currentId == startId) && reverse))
        {
            if (!loopAnimation)
            {
                Application::getInstance()->unregisterTimerWidget(this);
                running = false;
            }

            if (animationDoneAction && animationDoneAction->isValid())
            {
                animationDoneAction->execute(*this);
            }

            if (running && loopAnimation)
            {
                if (reverse)
                {
                    Image::setBitmap(Bitmap(endId));
                }
                else
                {
                    Image::setBitmap(Bitmap(startId));
                }
                invalidate();
            }
        }
        else
        {
            if (reverse)
            {
                --currentId;
            }
            else
            {
                ++currentId;
            }
            Image::setBitmap(Bitmap(currentId));
            invalidate();
        }
    }
}

void AnimatedImage::startAnimation(const bool& rev, const bool& reset, const bool& loop)
{
    if ((startId != BITMAP_INVALID) && (endId != BITMAP_INVALID))
    {
        reverse = rev;
        loopAnimation = loop;
        if (reverse && reset)
        {
            Image::setBitmap(Bitmap(endId));
            invalidate();
        }
        else if (!reverse && reset)
        {
            Image::setBitmap(Bitmap(startId));
            invalidate();
        }
        Application::getInstance()->registerTimerWidget(this);
        running = true;
    }
}

void AnimatedImage::stopAnimation()
{
    Application::getInstance()->unregisterTimerWidget(this);
    running = false;
    if (reverse)
    {
        Image::setBitmap(Bitmap(endId));
    }
    else
    {
        Image::setBitmap(Bitmap(startId));
    }
    invalidate();
}

void AnimatedImage::pauseAnimation()
{
    if (running)
    {
        Application::getInstance()->unregisterTimerWidget(this);
        running = false;
    }
    else
    {
        Application::getInstance()->registerTimerWidget(this);
        running = true;
    }
}

void AnimatedImage::setBitmaps(BitmapId start, BitmapId end)
{
    startId = start;
    endId = end;
    Image::setBitmap(Bitmap(startId));
}

void AnimatedImage::setUpdateTicksInterval(uint8_t updateInterval)
{
    updateTicksInterval = updateInterval;
    ticksSinceUpdate = 0;
}

} // namespace touchgfx
