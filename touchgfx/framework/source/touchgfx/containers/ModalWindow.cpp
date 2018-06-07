/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#include <touchgfx/containers/ModalWindow.hpp>
#include <touchgfx/Color.hpp>

namespace touchgfx
{

ModalWindow::ModalWindow() :
    Container()
{
    Container::setWidth(HAL::DISPLAY_WIDTH);
    Container::setHeight(HAL::DISPLAY_HEIGHT);

    int defaultShadeAlpha = 96;
    colortype defaultShadeColor = Color::getColorFrom24BitRGB(0x0, 0x0, 0x0);

    backgroundShade.setPosition(0, 0, getWidth(), getHeight());
    backgroundShade.setColor(defaultShadeColor);
    backgroundShade.setTouchable(true);
    ModalWindow::setShadeAlpha(defaultShadeAlpha);
    Container::add(backgroundShade);

    Container::add(windowContainer);
    windowContainer.add(windowBackground);
}

ModalWindow::~ModalWindow()
{
}

void ModalWindow::setBackground(const BitmapId& bmpId)
{
    windowBackground.setBitmap(Bitmap(bmpId));
    windowBackground.setXY(0, 0);

    windowContainer.setPosition((getWidth() - windowBackground.getWidth()) / 2, (getHeight() - windowBackground.getHeight()) / 2, windowBackground.getWidth(), windowBackground.getHeight());
    invalidate();
}

void ModalWindow::setBackground(const BitmapId& bmpId, int16_t backgroundX, int16_t backgroundY)
{
    setBackground(bmpId);
    windowContainer.setXY(backgroundX, backgroundY);
}

uint16_t ModalWindow::getBackgroundWidth() const
{
    return windowBackground.getWidth();
}

uint16_t ModalWindow::getBackgroundHeight() const
{
    return windowBackground.getHeight();
}

void ModalWindow::add(Drawable& d)
{
    windowContainer.add(d);
}

void ModalWindow::remove(Drawable& d)
{
    windowContainer.remove(d);
}

void ModalWindow::setShadeAlpha(uint8_t alpha)
{
    backgroundShade.setAlpha(alpha);
    backgroundShade.invalidate();
}

uint8_t ModalWindow::getShadeAlpha() const
{
    return backgroundShade.getAlpha();
}

void ModalWindow::setShadeColor(colortype color)
{
    backgroundShade.setColor(color);
    backgroundShade.invalidate();
}

touchgfx::colortype ModalWindow::getShadeColor() const
{
    return backgroundShade.getColor();
}

void ModalWindow::show()
{
    setVisible(true);
    invalidate();
}

void ModalWindow::hide()
{
    setVisible(false);
    invalidate();
}

bool ModalWindow::isShowing() const
{
    return isVisible();
}

}
