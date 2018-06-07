/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef SNAPSHOTWIDGET_HPP
#define SNAPSHOTWIDGET_HPP

#include <touchgfx/widgets/Widget.hpp>

namespace touchgfx
{
/**
 * @class SnapshotWidget SnapshotWidget.hpp touchgfx/widgets/SnapshotWidget.hpp
 *
 * @brief A widget that is able to make a snapshot of the area the SnapshotWidget covers.
 *
 *        A widget that is able to make a snapshot of the area the SnapshotWidget covers. The
 *        SnapshotWidget will show the snapshot captured when it is drawn.
 *
 * @see Widget
 */
class SnapshotWidget : public Widget
{
public:

    /**
     * @fn SnapshotWidget::SnapshotWidget();
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    SnapshotWidget();

    /**
     * @fn virtual SnapshotWidget::~SnapshotWidget();
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~SnapshotWidget();

    /**
     * @fn virtual void SnapshotWidget::draw(const Rect& invalidatedArea) const;
     *
     * @brief Draws the SnapshotWidget.
     *
     *        Draws the SnapshotWidget. It supports partial drawing, so it only redraws the
     *        area described by invalidatedArea.
     *
     * @param invalidatedArea The rectangle to draw, with coordinates relative to this drawable.
     */
    virtual void draw(const Rect& invalidatedArea) const;

    /**
     * @fn virtual Rect SnapshotWidget::getSolidRect() const;
     *
     * @brief Gets solid rectangle.
     *
     *        Gets solid rectangle.
     *
     * @return The solid rectangle.
     */
    virtual Rect getSolidRect() const;

    /**
     * @fn virtual void SnapshotWidget::makeSnapshot();
     *
     * @brief Makes a snapshot of the area the SnapshotWidget currently covers.
     *
     *        Makes a snapshot of the area the SnapshotWidget currently covers. This area is
     *        defined by setting the dimensions and the position of the SnapshotWidget.
     */
    virtual void makeSnapshot();

    /**
     * @fn void SnapshotWidget::setAlpha(const uint8_t a)
     *
     * @brief Sets the alpha value.
     *
     *        Sets the alpha value.
     *
     * @param a The alpha value.
     */
    void setAlpha(const uint8_t a)
    {
        alpha = a;
    }

    /**
     * @fn uint8_t SnapshotWidget::getAlpha() const
     *
     * @brief Gets the current alpha value.
     *
     *        Gets the current alpha value.
     *
     * @return The alpha value.
     */
    uint8_t getAlpha() const
    {
        return alpha;
    }

    /**
     * @fn virtual uint16_t SnapshotWidget::getType() const
     *
     * @brief For GUI testing only.
     *
     *        For GUI testing only. Returns type of this drawable.
     *
     * @return TYPE_SNAPSHOTWIDGET.
     */
    virtual uint16_t getType() const
    {
        return (uint16_t)TYPE_SNAPSHOTWIDGET;
    }

protected:
    uint16_t* fbCopy; ///< Pointer to the animation storage in which the pixel data for this snapshot is stored. Zero if no snapshot has been made.
    uint8_t   alpha;  ///< The alpha with which to draw this snapshot.
};

} // namespace touchgfx

#endif // SNAPSHOTWIDGET_HPP
