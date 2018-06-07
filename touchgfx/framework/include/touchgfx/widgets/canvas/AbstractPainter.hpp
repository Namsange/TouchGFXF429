/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef ABSTRACTPAINTER_HPP
#define ABSTRACTPAINTER_HPP

#include <stdint.h>

namespace touchgfx
{
/**
 * @class AbstractPainter AbstractPainter.hpp touchgfx/widgets/canvas/AbstractPainter.hpp
 *
 * @brief An abstract class for creating painter classes for drawing canvas widgets.
 *
 *        An abstract class for creating painter classes for drawing canvas widgets.
 */
class AbstractPainter
{
public:

    /**
     * @fn AbstractPainter::AbstractPainter();
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    AbstractPainter();

    /**
     * @fn virtual AbstractPainter::~AbstractPainter();
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~AbstractPainter();

    /**
     * @fn void AbstractPainter::setOffset(uint16_t offsetX, uint16_t offsetY);
     *
     * @brief Sets the offset of the area being drawn.
     *
     *        Sets the offset of the area being drawn. This allows render() to calculate the x,
     *        y relative to the widget, and not just relative to the invalidated area.
     *
     * @param offsetX The offset x coordinate of the invalidated area relative to the widget.
     * @param offsetY The offset y coordinate of the invalidated area relative to the widget.
     */
    void setOffset(uint16_t offsetX, uint16_t offsetY);

    /**
     * @fn virtual void AbstractPainter::render(uint8_t* ptr, int x, int xAdjust, int y, unsigned count, const uint8_t* covers) = 0;
     *
     * @brief Paint a designated part of the RenderingBuffer.
     *
     *        Paint a designated part of the RenderingBuffer with respect to the amount of
     *        coverage of each pixel given by the parameter covers.
     *
     * @param [in] ptr Pointer to the row in the RenderingBuffer.
     * @param x        The x coordinate.
     * @param xAdjust  The minor adjustment of x (used when a pixel is smaller than a byte to
     *                 specify that the pointer should have been advanced "xAdjust" pixels
     *                 futher).
     * @param y        The y coordinate.
     * @param count    Number of pixels to fill.
     * @param covers   The coverage in of each pixel.
     */
    virtual void render(uint8_t* ptr, int x, int xAdjust, int y, unsigned count, const uint8_t* covers) = 0;

protected:

    /**
     * @fn void AbstractPainter::setWidgetAlpha(uint8_t alpha);
     *
     * @brief Sets widget alpha.
     *
     *        Sets the widget alpha to allow an entire canvas widget to easily be faded without
     *        changing the painter of the widget.
     *
     * @param alpha The alpha.
     *
     * @note Used internally by Canvas.
     */
    void setWidgetAlpha(uint8_t alpha);

    int16_t areaOffsetX; ///< The offset x coordinate of the area being drawn
    int16_t areaOffsetY; ///< The offset y coordinate of the area being drawn
    uint8_t widgetAlpha; ///< The alpha of the widget using the painter

    friend class Canvas;
}; // class Painter

} // namespace touchgfx

#endif // ABSTRACTPAINTER_HPP
