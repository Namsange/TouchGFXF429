#include "stm32f4xx_hal.h"
#include "Bsp.h"

void MX_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin (GPIOH, LED1_Pin | LED2_Pin | LED3_Pin, GPIO_PIN_SET);
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin (GPIOD, CTP_RST_Pin | CTP_INT_Pin, GPIO_PIN_RESET);
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin (GPIOD, LTDC_DISP_Pin | LTDC_BL_Pin, GPIO_PIN_SET);
    /*Configure GPIO pins : PHPin PHPin PHPin */
    GPIO_InitStruct.Pin = LED1_Pin | LED2_Pin | LED3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init (GPIOH, &GPIO_InitStruct);
    /*Configure GPIO pins : PDPin PDPin */
    GPIO_InitStruct.Pin = CTP_RST_Pin | CTP_INT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init (GPIOD, &GPIO_InitStruct);
    /*Configure GPIO pins : PDPin PDPin */
    GPIO_InitStruct.Pin = LTDC_DISP_Pin | LTDC_BL_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init (GPIOD, &GPIO_InitStruct);
}
