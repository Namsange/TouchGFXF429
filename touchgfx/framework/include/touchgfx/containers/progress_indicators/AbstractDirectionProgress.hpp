/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef ABSTRACTDIRECTIONPROGRESS_HPP
#define ABSTRACTDIRECTIONPROGRESS_HPP

#include <touchgfx/containers/progress_indicators/AbstractProgressIndicator.hpp>

namespace touchgfx
{

/**
 * @class AbstractDirectionProgress AbstractDirectionProgress.hpp touchgfx/containers/progress_indicators/AbstractDirectionProgress.hpp
 *
 * @brief An abstract direction progress.
 *
 *        An abstract direction progress for progress indicators that need a direction to be specified.
 */
class AbstractDirectionProgress : public AbstractProgressIndicator
{
public:

    /**
     * @typedef enum DirectionType
     *
     * @brief Values that represent directions.
     *
     *        Values that represent directions.
     */
    typedef enum
    {
        RIGHT,
        LEFT,
        DOWN,
        UP
    } DirectionType;

    /**
     * @fn AbstractDirectionProgress::AbstractDirectionProgress();
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    AbstractDirectionProgress();

    /**
     * @fn virtual AbstractDirectionProgress::~AbstractDirectionProgress();
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~AbstractDirectionProgress();

    /**
     * @fn virtual void AbstractDirectionProgress::setDirection(DirectionType direction);
     *
     * @brief Sets a direction.
     *
     *        Sets a direction.
     *
     * @param direction The direction.
     */
    virtual void setDirection(DirectionType direction);

    /**
     * @fn virtual DirectionType AbstractDirectionProgress::getDirection() const;
     *
     * @brief Gets the direction.
     *
     *        Gets the direction.
     *
     * @return The direction.
     */
    virtual DirectionType getDirection() const;

protected:
    DirectionType progressDirection;    ///< The progress direction
};

}

#endif // ABSTRACTDIRECTIONPROGRESS_HPP
