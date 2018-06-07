/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef EVENT_HPP
#define EVENT_HPP

namespace touchgfx
{
/**
 * @class Event Event.hpp touchgfx/Event.hpp
 *
 * @brief Simple base class for events.
 *
 *        Simple base class for events.
 */
class Event
{
public:

    /**
     * @typedef enum EventType
     *
     * @brief The events types.
     *
     *        The events types.
     */
    typedef enum
    {
        EVENT_CLICK,  ///< A click
        EVENT_DRAG,   ///< A drag
        EVENT_GESTURE ///< A gesture
    } EventType;

    Event() { }

    /**
     * @fn virtual EventType Event::getEventType() = 0;
     *
     * @brief Gets event type.
     *
     *        Gets event type.
     *
     * @return The type of this event.
     */
    virtual EventType getEventType() = 0;

    /**
     * @fn virtual Event::~Event()
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~Event() { }
};

} // namespace touchgfx

#endif // EVENT_HPP
