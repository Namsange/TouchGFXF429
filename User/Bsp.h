#ifndef _BSP_H_
#define _BSP_H_

#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOH
#define LED2_Pin GPIO_PIN_11
#define LED2_GPIO_Port GPIOH
#define LED3_Pin GPIO_PIN_12
#define LED3_GPIO_Port GPIOH
#define CTP_RST_Pin GPIO_PIN_11
#define CTP_RST_GPIO_Port GPIOD
#define CTP_INT_Pin GPIO_PIN_12
#define CTP_INT_GPIO_Port GPIOD
#define LTDC_DISP_Pin GPIO_PIN_4
#define LTDC_DISP_GPIO_Port GPIOD
#define LTDC_BL_Pin GPIO_PIN_7
#define LTDC_BL_GPIO_Port GPIOD

extern void MX_GPIO_Init(void);

#endif
