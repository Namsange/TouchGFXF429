/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef CLICKLISTENER_HPP
#define CLICKLISTENER_HPP

#include <touchgfx/Callback.hpp>

namespace touchgfx
{
/**
 * @class ClickListener ClickListener.hpp touchgfx/mixins/ClickListener.hpp
 *
 * @brief Mix-in class that extends a class with a click action event.
 *
 *        Mix-in class that extends a class with a click action event that is called when the
 *        class receives a click event.
 *
 * @tparam T specifies the type to extend with the ClickListener behavior.
 */
template<class T>
class ClickListener : public T
{
public:

    /**
     * @fn ClickListener::ClickListener()
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    ClickListener() : T(), clickAction(0)
    {
        T::setTouchable(true);
    }

    /**
     * @fn virtual ClickListener::~ClickListener()
     *
     * @brief Destructor.
     */
    virtual ~ClickListener() { }

    /**
     * @fn virtual void ClickListener::handleClickEvent(const ClickEvent& event)
     *
     * @brief Ensures that the clickEvent is propagated to the super class.
     *
     *         Ensures that the clickEvent is propagated to the super class T and to the
     *         clickAction listener.
     *
     * @param event Information about the click.
     *
     * @see Drawable::handleClickEvent()
     */
    virtual void handleClickEvent(const ClickEvent& event)
    {
        T::handleClickEvent(event);
        if (clickAction && clickAction->isValid())
        {
            clickAction->execute(*this, event);
        }
    }

    /**
     * @fn void ClickListener::setClickAction(GenericCallback< const T&, const ClickEvent& >& callback)
     *
     * @brief Associates an action to be performed when the class T is clicked.
     *
     *        Associates an action to be performed when the class T is clicked.
     *
     * @param callback The callback to be executed. The callback will be given a reference to T.
     *
     * @see GenericCallback
     */
    void setClickAction(GenericCallback< const T&, const ClickEvent& >& callback)
    {
        clickAction = &callback;
    }

protected:
    GenericCallback<const T&, const ClickEvent&>* clickAction;  ///< The callback to be executed when T is clicked
};

} //namespace touchgfx

#endif // CLICKLISTENER_HPP
