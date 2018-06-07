/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef VIEW_HPP
#define VIEW_HPP

#include <touchgfx/Screen.hpp>
#include <mvp/Presenter.hpp>

namespace touchgfx
{
/**
 * @class View View.hpp mvp/View.hpp
 *
 * @brief This is a generic touchgfx::Screen specialization for normal applications.
 *
 *        This is a generic touchgfx::Screen specialization for normal applications. It
 *        provides a link to the Presenter class.
 *
 * @note All views in the application must be a subclass of this type.
 *
 * @tparam T The type of Presenter associated with this view.
 *
 * @see Screen
 */
template<class T>
class View : public Screen
{
public:

    /**
     * @fn View::View()
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    View() : presenter(0)
    {
    }

    /**
     * @fn void View::bind(T& presenter)
     *
     * @brief Binds an instance of a specific Presenter type (subclass) to the View instance.
     *
     *        Binds an instance of a specific Presenter type (subclass) to the View instance.
     *        This function is called automatically when a new presenter/view pair is activated.
     *
     * @param [in] presenter The specific Presenter to be associated with the View.
     */
    void bind(T& presenter)
    {
        this->presenter = &presenter;
    }

protected:
    T* presenter;   ///< Pointer to the Presenter associated with this view.
};

} // namespace touchgfx
#endif // VIEW_HPP
