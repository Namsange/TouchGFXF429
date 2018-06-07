/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef NOTRANSITION_HPP
#define NOTRANSITION_HPP

#include <touchgfx/transitions/Transition.hpp>

namespace touchgfx
{
/**
 * @class NoTransition NoTransition.hpp touchgfx/transitions/NoTransition.hpp
 *
 * @brief The most simple Transition without any visual effects.
 *
 *        The most simple Transition without any visual effects.
 *
 * @see Transition
 */
class NoTransition : public Transition
{
public:

    /**
     * @fn NoTransition::NoTransition()
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    NoTransition() : Transition() { }

    /**
     * @fn virtual NoTransition::~NoTransition()
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~NoTransition() { }

    /**
     * @fn virtual void NoTransition::handleTickEvent()
     *
     * @brief Indicates that the transition is done after the first tick.
     *
     *        Indicates that the transition is done after the first tick.
     */
    virtual void handleTickEvent()
    {
        done = true;
    }
};

} // namespace touchgfx
#endif // NOTRANSITION_HPP
