/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef ABSTRACTSHAPE_HPP
#define ABSTRACTSHAPE_HPP

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/widgets/Widget.hpp>

#include <touchgfx/widgets/canvas/CanvasWidget.hpp>

namespace touchgfx
{
/**
 * @class AbstractShape AbstractShape.hpp touchgfx/widgets/canvas/AbstractShape.hpp
 *
 * @brief Simple widget capable of drawing a abstractShape.
 *
 *        Simple widget capable of drawing a abstractShape. The abstractShape can be scaled and
 *        rotated around 0,0. Note that the y axis goes down, so a abstractShape that goes up
 *        must be given negative coordinates.
 *
 * @see CanvasWidget
 *
 * ### tparam T The type of the points used for the abstractShape. Must be int or float.
 */
class AbstractShape : public CanvasWidget
{
public:

    /**
     * @struct ShapePoint AbstractShape.hpp touchgfx/widgets/canvas/AbstractShape.hpp
     *
     * @brief Defines an alias representing the array of points making up the abstract shape.
     *
     *        Defines an alias representing the array of points making up the abstract shape.
     *        This will help setting up the abstractShape very easily using setAbstractShape().
     *
     * @tparam T Generic type parameter.
     *
     * @see setAbstractShape()
     */
    template <class T>
    struct ShapePoint
    {
        T x; ///< The x coordinate of the points.
        T y; ///< The y coordinate of the points.
    };

    /**
     * @fn AbstractShape::AbstractShape();
     *
     * @brief Constructs a new AbstractShape.
     *
     *        Constructs a new AbstractShape.
     */
    AbstractShape();

    /**
     * @fn virtual AbstractShape::~AbstractShape();
     *
     * @brief Virtual Destructor.
     *
     *        Virtual Destructor.
     */
    virtual ~AbstractShape();

    /**
     * @fn virtual int AbstractShape::getNumPoints() const = 0;
     *
     * @brief Gets number points used to make up the shape.
     *
     *        Gets number points used to make up the shape.
     *
     * @return The number points.
     */
    virtual int getNumPoints() const = 0;

    /**
     * @fn virtual void AbstractShape::setCorner(int i, CWRUtil::Q5 x, CWRUtil::Q5 y) = 0;
     *
     * @brief Sets a corner of the shape.
     *
     *        Sets a corner of the shape in Q5 format.
     *
     * @param i Zero-based index of the corner.
     * @param x The x coordinate in Q5 format.
     * @param y The y coordinate in Q5 format.
     *
     * @note Remember to call updateAbstractShapeCache() to make sure that the cached outline of
     *       the shape is correct.
     * @see updateAbstractShapeCache
     */
    virtual void setCorner(int i, CWRUtil::Q5 x, CWRUtil::Q5 y) = 0;

    /**
     * @fn virtual CWRUtil::Q5 AbstractShape::getCornerX(int i) const = 0;
     *
     * @brief Gets the x coordinate of a corner.
     *
     *        Gets the x coordinate of a corner.
     *
     * @param i Zero-based index of the corner.
     *
     * @return The corner x coordinate.
     */
    virtual CWRUtil::Q5 getCornerX(int i) const = 0;

    /**
     * @fn virtual CWRUtil::Q5 AbstractShape::getCornerY(int i) const = 0;
     *
     * @brief Gets the y coordinate of a corner.
     *
     *        Gets the y coordinate of a corner.
     *
     * @param i Zero-based index of the corner.
     *
     * @return The corner y coordinate.
     */
    virtual CWRUtil::Q5 getCornerY(int i) const = 0;

    /**
     * @fn template <class T> void AbstractShape::setShape(ShapePoint<T>* points)
     *
     * @brief Sets a shape the struct Points.
     *
     *        Sets a shape the struct Points. The cached outline of the shape is automatically
     *        updated.
     *
     * @tparam T Generic type parameter, either int or float.
     * @param [in] points The points that make up the shape.
     *
     * @note The area containing the shape is not invalidated.
     */
    template <class T>
    void setShape(ShapePoint<T>* points)
    {
        int numPoints = getNumPoints();
        for (int i = 0; i < numPoints; i++)
        {
            setCorner(i, CWRUtil::toQ5(points[i].x), CWRUtil::toQ5(points[i].y));
        }
        updateAbstractShapeCache();
    }

    /**
     * @fn template <class T> void AbstractShape::setOrigin(T x, T y)
     *
     * @brief Sets the position of (0,0).
     *
     *        Sets the position of (0,0) used when the abstractShape was created. This means
     *        that all coordinates initially used when created the shape are moved relative to
     *        these given offsets. Calling setOrigin() again, will not add to the previous
     *        settings of setOrigin() but will replace the old values for origin.
     *
     * @note The area containing the AbstractShape is not invalidated.
     *
     * @tparam T Generic type parameter, either int or float.
     * @param x The x coordinate of the shapes position (0,0).
     * @param y The y coordinate of the shapes position (0,0).
     *
     * @see moveOrigin()
     */
    template <class T>
    void setOrigin(T x, T y)
    {
        CWRUtil::Q5 dxNew = CWRUtil::toQ5(x);
        CWRUtil::Q5 dyNew = CWRUtil::toQ5(y);

        if (dx == dxNew && dy == dyNew)
        {
            return;
        }

        dx = dxNew;
        dy = dyNew;

        updateAbstractShapeCache();
    }

    /**
     * @fn template <class T> void AbstractShape::moveOrigin(T x, T y)
     *
     * @brief Moves the start point for this AbstractShape.
     *
     *        Moves the start point for this AbstractShape. The rectangle that surrounds the
     *        old and new area covered by the shape will be invalidated.
     *
     * @note The area containing the AbstractShape is invalidated before and after the change.
     *
     * @tparam T Generic type parameter, either int or float.
     * @param x The x coordinate of the shapes position (0,0).
     * @param y The y coordinate of the shapes position (0,0).
     *
     * @see setOrigin()
     */
    template <class T>
    void moveOrigin(T x, T y)
    {
        CWRUtil::Q5 xNew = CWRUtil::toQ5(x);
        CWRUtil::Q5 yNew = CWRUtil::toQ5(y);

        if (dx == xNew && dy == yNew)
        {
            return;
        }

        Rect rect = getMinimalRect();

        dx = xNew;
        dy = yNew;

        updateAbstractShapeCache();

        rect.expandToFit(getMinimalRect());
        invalidateRect(rect);
    }

    /**
     * @fn template <class T> void AbstractShape::getOrigin(T& dx, T& dy) const
     *
     * @brief Gets the start coordinates for the line.
     *
     *        Gets the start coordinates for the line.
     *
     * @tparam T Generic type parameter, either int or float.
     * @param [out] dx The x coordinate.
     * @param [out] dy The y coordinate.
     */
    template <class T>
    void getOrigin(T& dx, T& dy) const
    {
        dx = int(this->dx) / T(Rasterizer::POLY_BASE_SIZE);
        dy = int(this->dy) / T(Rasterizer::POLY_BASE_SIZE);
    }

    /**
     * @fn void AbstractShape::setAngle(int angle);
     *
     * @brief Sets the angle to turn the abstractShape.
     *
     *        Sets the angle to turn the abstractShape. 0 degrees is straight up and 90 degrees
     *        is 3 o'clock.
     *
     * @note The area containing the AbstractShape is not invalidated.
     *
     * @param angle The angle to turn the abstractShape to relative to 0 (straight up), not
     *              relative to the previous angle.
     *
     * @see updateAngle()
     */
    void setAngle(int angle);

    /**
     * @fn void AbstractShape::updateAngle(int angle);
     *
     * @brief Sets the angle to turn the abstractShape.
     *
     *        Sets the angle to turn the abstractShape. 0 degrees is straight up and 90 degrees
     *        is 3 o'clock.
     *
     * @note The area containing the AbstractShape is invalidated before and after the change.
     *
     * @param angle The angle to turn the abstractShape.
     *
     * @see setAngle()
     */
    void updateAngle(int angle);

    /**
     * @fn int AbstractShape::getAngle() const;
     *
     * @brief Gets the current angle of the abstractShape.
     *
     *        Gets the current angle of the abstractShape.
     *
     * @return The angle of the AbstractShape.
     */
    int getAngle() const;

    /**
     * @fn template <class T> void AbstractShape::setScale(T newXScale, T newYScale)
     *
     * @brief Scale the AbstractShape.
     *
     *        Scale the AbstractShape the given amount in the x direction and the y direction.
     *
     * @tparam T Generic type parameter.
     * @param newXScale The new scale in the x direction.
     * @param newYScale The new scale in the y direction.
     *
     * @note The area containing the AbstractShape is not invalidated.
     *
     * @see getScale(), updateScale()
     */
    template <class T>
    void setScale(T newXScale, T newYScale)
    {
        xScale = CWRUtil::toQ5(newXScale);
        yScale = CWRUtil::toQ5(newYScale);
        updateAbstractShapeCache();
    }

    /**
     * @fn template <class T> void AbstractShape::setScale(T scale)
     *
     * @brief Scale the AbstractShape.
     *
     *        Scale the AbstractShape the given amount in the x direction and the y direction.
     *
     * @note The area containing the AbstractShape is not invalidated.
     *
     * @tparam T Generic type parameter, either int or float.
     * @param scale The scale in the x direction.
     *
     * @see getScale()
     */
    template <class T>
    void setScale(T scale)
    {
        setScale(scale, scale);
    }

    /**
     * @fn virtual bool AbstractShape::drawCanvasWidget(const Rect& invalidatedArea) const;
     *
     * @brief Draws the AbstractShape.
     *
     *        Draws the AbstractShape. This class supports partial drawing, so only the area
     *        described by the rectangle will be drawn.
     *
     * @param invalidatedArea The rectangle to draw, with coordinates relative to this drawable.
     *
     * @return true if it succeeds, false if it fails.
     */
    virtual bool drawCanvasWidget(const Rect& invalidatedArea) const;

    /**
     * @fn void AbstractShape::updateAbstractShapeCache();
     *
     * @brief Updates the abstractShape cache.
     *
     *        Updates the abstractShape cache. The cache is used to be able to quickly redraw
     *        the AbstractShape without calculating the points that make up the abstractShape
     *        (with regards to scaling and rotation).
     */
    void updateAbstractShapeCache();

protected:
    /**
    * @fn virtual void AbstractShape::setCache(int i, CWRUtil::Q5 x, CWRUtil::Q5 y) = 0;
    *
    * @brief Sets the cached coordinates of a given corner.
    *
    *        Sets the cached coordinates of a given corner. The coordinates in the cache are
    *        the coordinates from the corners after rotating and scaling the coordinate.
    *
    * @param i Zero-based index of the corner.
    * @param x The x coordinate.
    * @param y The y coordinate.
    */
    virtual void setCache(int i, CWRUtil::Q5 x, CWRUtil::Q5 y) = 0;

    /**
    * @fn virtual CWRUtil::Q5 AbstractShape::getCacheX(int i) const = 0;
    *
    * @brief Gets cached x coordinate of a corner.
    *
    *        Gets cached x coordinate of a corner.
    *
    * @param i Zero-based index of the corner.
    *
    * @return The cached x coordinate.
    */
    virtual CWRUtil::Q5 getCacheX(int i) const = 0;

    /**
    * @fn virtual CWRUtil::Q5 AbstractShape::getCacheY(int i) const = 0;
    *
    * @brief Gets cached y coordinate of a corner.
    *
    *        Gets cached y coordinate of a corner.
    *
    * @param i Zero-based index of the corner.
    *
    * @return The cached y coordinate.
    */
    virtual CWRUtil::Q5 getCacheY(int i) const = 0;

    /**
     * @fn virtual Rect AbstractShape::getMinimalRect() const;
     *
     * @brief Gets minimal rectangle containing the abstractShape.
     *
     *        Gets minimal rectangle containing the abstractShape. Used for invalidating only
     *        the required part of the screen.
     *
     * @return The minimal rectangle.
     */
    virtual Rect getMinimalRect() const;

private:
    CWRUtil::Q5 dx, dy;
    int shapeAngle;
    CWRUtil::Q5 xScale, yScale;
    CWRUtil::Q5 xMin, yMin, xMax, yMax;
};

} // namespace touchgfx

#endif // ABSTRACTSHAPE_HPP
