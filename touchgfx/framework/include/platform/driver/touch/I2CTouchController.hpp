/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef I2CTOUCHCONTROLLER_HPP
#define I2CTOUCHCONTROLLER_HPP

#include <touchgfx/hal/Types.hpp>
#include <platform/driver/touch/TouchController.hpp>
#include <platform/driver/i2c/I2C.hpp>

namespace touchgfx
{
/**
 * @class I2CTouchController I2CTouchController.hpp platform/driver/touch/I2CTouchController.hpp
 *
 * @brief Specific I2C-enabled type of Touch Controller.
 *
 *        Specific I2C-enabled type of Touch Controller.
 *
 * @sa TouchController
 */
class I2CTouchController : public TouchController
{
public:
    /**
     * @fn I2CTouchController::I2CTouchController(I2C& i2c)
     *
     * @brief Constructor.
     *
     *        Constructor. Initializes I2C driver.
     *
     * @param [in,out] i2c I2C driver.
     */
    I2CTouchController(I2C& i2c):
        i2c(i2c)
    {
        i2c.init();
    }

    /**
     * @fn virtual I2CTouchController::~I2CTouchController()
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~I2CTouchController()
    {
    }

    /**
     * @fn virtual void I2CTouchController::init() = 0;
     *
     * @brief Initializes touch controller.
     *
     *        Initializes touch controller.
     */
    virtual void init() = 0;

    /**
     * @fn virtual bool I2CTouchController::sampleTouch(int32_t& x, int32_t& y) = 0;
     *
     * @brief Checks whether the touch screen is being touched.
     *
     *        Checks whether the touch screen is being touched, and if so, what coordinates.
     *
     * @param [out] x The x position of the touch
     * @param [out] y The y position of the touch
     *
     * @return True if a touch has been detected, otherwise false.
     */
    virtual bool sampleTouch(int32_t& x, int32_t& y) = 0;

protected:
    I2C& i2c; ///< I2C driver
};

} // namespace touchgfx

#endif // I2CTOUCHCONTROLLER_HPP
