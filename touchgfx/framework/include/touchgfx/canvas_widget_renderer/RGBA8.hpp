/******************************************************************************
 * This file is part of the TouchGFX 4.9.3 distribution.
 * Copyright (C) 2017 Draupner Graphics A/S <http://www.touchgfx.com>.
 ******************************************************************************
 * This is licensed software. Any use hereof is restricted by and subject to 
 * the applicable license terms. For further information see "About/Legal
 * Notice" in TouchGFX Designer or in your TouchGFX installation directory.
 *****************************************************************************/

#ifndef RGBA8_HPP
#define RGBA8_HPP

#include <touchgfx/hal/Types.hpp>

namespace touchgfx
{
/**
 * @struct RGBA8 RGBA8.hpp touchgfx/canvas_widget_renderer/RGBA8.hpp
 *
 * @brief Deprecated, use colortype instead.
 *
 * @note Deprecated, use colortype instead.
 *
 * @see colortype
 */
struct RGBA8
{
    uint8_t red;   ///< The red part of the color.
    uint8_t green; ///< The green part of the color.
    uint8_t blue;  ///< The blue part of the color.
    uint8_t alpha; ///< The alpha value of the color, specifying how transparent the color is  (0 = invisible, 255 = solid).

    /**
     * @fn RGBA8()
     *
     * @brief Default constructor. Deprecated, use colortype instead.
     *
     *        Deprecated, use colortype instead.
     *
     * @note Deprecated, use colortype instead.
     *
     * @see colortype
     */
    RGBA8() : red(0), green(0), blue(0), alpha(0) { }

    /**
     * @fn RGBA8(uint16_t rgb565, unsigned alpha_ = 255)
     *
     * @brief Constructor. Deprecated, use colortype instead.
     *
     *        Deprecated, use colortype instead.
     *
     * @note Deprecated, use colortype instead.
     *
     * @param rgb565 RGB565 encoded color.
     * @param alpha_ alpha value, specifying the transparency of the color (0 = invisible, 255 =
     *               solid).
     *
     * @see colortype
     */
    RGBA8(uint16_t rgb565, unsigned alpha_ = 255) :
        red(uint8_t((rgb565 & 0xF800) >> 8)),
        green(uint8_t((rgb565 & 0x07E0) >> 3)),
        blue(uint8_t((rgb565 & 0x001F) << 3)),
        alpha(uint8_t(alpha_))
    {
        red |= red >> 5;
        green |= green >> 6;
        blue |= blue >> 5;
    }

    /**
     * @fn RGBA8(unsigned red_, unsigned green_, unsigned blue_, unsigned alpha_ = 255)
     *
     * @brief Constructor. Deprecated, use colortype instead.
     *
     *        Deprecated, use colortype instead.
     *
     * @note Deprecated, use colortype instead.
     *
     * @param red_   The red part of the color.
     * @param green_ The green part of the color.
     * @param blue_  The blue part of the color.
     * @param alpha_ alpha value, specifying the transparency of the color (0 = invisible, 255 =
     *               solid).
     *
     * @see colortype
     */
    RGBA8(unsigned red_, unsigned green_, unsigned blue_, unsigned alpha_ = 255) :
        red(uint8_t(red_)),
        green(uint8_t(green_)),
        blue(uint8_t(blue_)),
        alpha(uint8_t(alpha_))
    {
    }
};

} // namespace touchgfx

#endif // RGBA8_HPP
