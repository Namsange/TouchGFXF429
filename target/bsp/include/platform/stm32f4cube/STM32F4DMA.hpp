#ifndef STM32F4DMA_HPP
#define STM32F4DMA_HPP

#include <touchgfx/hal/DMA.hpp>

#ifndef NO_USING_NAMESPACE_TOUCHGFX
using namespace touchgfx;
#endif

/**
 * @class STM32F4DMA STM32F4DMA.hpp platform/hal/ST/mcu/stm32f4x9/STM32F4DMA.hpp
 *
 * @brief This class specializes DMA_Interface for the ST F4xx processors.
 *
 *        This class specializes DMA_Interface for the ST F4xx processors. Based on the ST CubeF4 API.
 *
 * @sa touchgfx::DMA_Interface
 */
class STM32F4DMA : public touchgfx::DMA_Interface
{
    /**
     * @typedef touchgfx::DMA_Interface Base
     *
     * @brief Defines an alias representing the base.
     *
     Defines an alias representing the base.
     */
    typedef touchgfx::DMA_Interface Base;
public:
    /**
     * @fn STM32F4DMA::STM32F4DMA();
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    STM32F4DMA();

    /**
     * @fn STM32F4DMA::~STM32F4DMA();
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~STM32F4DMA();

    /**
     * @fn touchgfx::BlitOperations STM32F4DMA::getBlitCaps();
     *
     * @brief Gets the blit capabilities.
     *
     *        Gets the blit capabilities.
     *
     *        This DMA supports a range of blit caps: BLIT_OP_COPY, BLIT_OP_COPY_ARGB8888,
     *        BLIT_OP_COPY_ARGB8888_WITH_ALPHA, BLIT_OP_COPY_A4, BLIT_OP_COPY_A8.
     *
     * @note For demonstration purposes, the blitcaps can be overridden at runtime to return zero
     *       by setting the overrideBlitCaps boolean to true.
     *
     * @return Currently supported blitcaps.
     */
    virtual touchgfx::BlitOperations getBlitCaps();

    /**
     * @fn void STM32F4DMA::initialize();
     *
     * @brief Perform hardware specific initialization.
     *
     *        Perform hardware specific initialization.
     */
    virtual void initialize();

    /**
     * @fn void STM32F4DMA::signalDMAInterrupt()
     *
     * @brief Raises a DMA interrupt signal.
     *
     *        Raises a DMA interrupt signal.
     */
    virtual void signalDMAInterrupt()
    {
        executeCompleted();
    }

protected:
    /**
     * @fn virtual void STM32F4DMA::setupDataCopy(const touchgfx::BlitOp& blitOp);
     *
     * @brief Configures the DMA for copying data to the frame buffer.
     *
     *        Configures the DMA for copying data to the frame buffer.
     *
     * @param blitOp Details on the copy to perform.
     */
    virtual void setupDataCopy(const touchgfx::BlitOp& blitOp);

    /**
     * @fn virtual void STM32F4DMA::setupDataFill(const touchgfx::BlitOp& blitOp);
     *
     * @brief Configures the DMA for "filling" the frame-buffer with a single color.
     *
     *        Configures the DMA for "filling" the frame-buffer with a single color.
     *
     * @param blitOp Details on the "fill" to perform.
     */
    virtual void setupDataFill(const touchgfx::BlitOp& blitOp);

    /**
     * @fn virtual void STM32F4DMA::setupFillWithAlpha(const touchgfx::BlitOp& blitOp);
     *
     * @brief Configures the DMA for blending the frame-buffer with a single color.
     *
     *        Configures the DMA for blending the frame-buffer with a single color.
     *
     * @param blitOp Details on the blend to perform.
     */
    virtual void setupFillWithAlpha(const touchgfx::BlitOp& blitOp);
    /**
     * Empty implementation since alpha channel is handled inside setupData functions.
     * @param alpha Ignored.
     */
    virtual void enableAlpha(uint8_t alpha) {}
private:
    /**
     * @fn bool STM32F4DMA::finished();
     *
     * @brief Interrupt call-back: Used for DMA transfers.
     *
     *        Interrupt call-back: Used for DMA transfers, which are known to complete the
     *        current BlitOp processing.
     *
     * @return true always (since the BlitOp processing has been completed).
     */
    bool finished();

    static const unsigned int channel = 0;    ///< The used DMA channel. Only channel 0 supports 2D transfers

    touchgfx::LockFreeDMA_Queue dma_queue;
    touchgfx::BlitOp            queue_storage[96];
    const touchgfx::BlitOp*     pBlitOp;      ///< Reference to current BlitOp (the queue is in-accessible from outside DMA_Interface)
    uint16_t                    numLines;     ///< Number of lines remaining in current transfer.
    uint8_t                     deadTime;
    unsigned                    use32Bit : 1; ///< Set to non-zero when using 32bit transfers (optimization)
};

#endif // STM32F4DMA_HPP
