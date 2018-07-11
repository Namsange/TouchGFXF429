#include "GT9157.h"
#include "stm32f4xx_hal_gpio.h"
#include "Bsp.h"
#include <string.h>
#define GTP_MAX_TOUCH     (5)
#define GTP_REG_VERSION    (0x8140)
#define GTP_READ_COOR_ADDR (0x814E)
#define GTP_REG_CONFIG_DATA (0x8047)
uint8_t GT9157[GTP_MAX_TOUCH] = {0};

uint8_t config[GTP_CONFIG_MAX_LENGTH + GTP_ADDR_LENGTH]
    = {GTP_REG_CONFIG_DATA >> 8, GTP_REG_CONFIG_DATA & 0xff};
uint8_t  end_cmd[3] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF, 0};
// static uint8_t GT9157_GetInstance (uint16_t DeviceAddr);
static void GTP_I2C_Write (uint8_t DeviceAddr, uint8_t * buf, int32_t len);
static void GTP_I2C_Read (uint8_t DeviceAddr, uint8_t * buf, int32_t len);
// static void GT9157_DisableGlobalIT (void);
// static void GT9157_EnableGlobalIT (void);
uint8_t CTP_CFG_GT9157[] = {
    0x00, 0x20, 0x03, 0xE0, 0x01, 0x05, 0x3C, 0x00, 0x01, 0x08,
    0x28, 0x0C, 0x50, 0x32, 0x03, 0x05, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x17, 0x19, 0x1E, 0x14, 0x8B, 0x2B, 0x0D,
    0x33, 0x35, 0x0C, 0x08, 0x00, 0x00, 0x00, 0x9A, 0x03, 0x11,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00,
    0x00, 0x20, 0x58, 0x94, 0xC5, 0x02, 0x00, 0x00, 0x00, 0x04,
    0xB0, 0x23, 0x00, 0x93, 0x2B, 0x00, 0x7B, 0x35, 0x00, 0x69,
    0x41, 0x00, 0x5B, 0x4F, 0x00, 0x5B, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x10,
    0x12, 0x14, 0x16, 0x18, 0x1A, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0F,
    0x10, 0x12, 0x13, 0x16, 0x18, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
    0x21, 0x22, 0x24, 0x26, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x48, 0x01
};

TS_DrvTypeDef GT9157_ts_drv = {
    GT9157_Init,
    GT9157_ReadID,
    GT9157_Reset,
    GT9157_TS_Start,
    GT9157_TS_DetectTouch,
    GT9157_TS_GetXY,
    GT9157_TS_EnableIT,
    GT9157_TS_ClearIT,
    GT9157_TS_ITStatus,
    GT9157_TS_DisableIT,
};

void GT9157_Init (uint16_t DeviceAddr)
{
    //uint8_t instance;
    //uint8_t empty;
	uint32_t i;
    uint8_t * cfg_info;
    uint8_t cfg_info_len;
    uint8_t check_sum = 0;
    uint8_t cfg_num = 0x80FE - 0x8047 + 1 ;

    IOE_Init();//配置GPIO口和i2c的属性
    BSP_GT9157_IO_Reset();//复位INT与RESET管脚，选中器械地址为0xBA
    IOE_ITGT9157Config();//使能INT中断口

    cfg_info =  CTP_CFG_GT9157;                     //指向寄存器配置
    cfg_info_len = CFG_GROUP_LEN (CTP_CFG_GT9157);  //计算配置表的大小
    memset (&config[GTP_ADDR_LENGTH], 0, GTP_CONFIG_MAX_LENGTH);
    memcpy (&config[GTP_ADDR_LENGTH], cfg_info, cfg_info_len);

    check_sum = 0;
    for (i = GTP_ADDR_LENGTH; i < cfg_num + GTP_ADDR_LENGTH; i++) {
        check_sum += config[i];
    }

    config[ cfg_num + GTP_ADDR_LENGTH] = (~check_sum) + 1; 	//checksum
    config[ cfg_num + GTP_ADDR_LENGTH + 1] =  1; 			//refresh 配置更新标志

    //写入配置信息
    GTP_I2C_Write (DeviceAddr, config, cfg_num + GTP_ADDR_LENGTH + 2);
    IOE_ITGT9157Config();
}
void GT9157_Reset(uint16_t DeviceAddr)
{
    BSP_GT9157_IO_Reset();
}
uint16_t GT9157_ReadID (uint16_t DeviceAddr)
{
    uint16_t touchIC = 0;
    uint8_t buf[8] = {GTP_REG_VERSION >> 8, GTP_REG_VERSION & 0xff};    //寄存器地址

    GTP_I2C_Read (DeviceAddr, buf, 8);

    if (buf[5] == 0x00) {
        //GT911芯片
        if (buf[2] == '9' && buf[3] == '1' && buf[4] == '1') {
            touchIC = 0x0911;
        }
    }
    else {
        //GT9157芯片
        if (buf[2] == '9' && buf[3] == '1' && buf[4] == '5' && buf[5] == '7') {
            touchIC = GT9157_ID;
        }
    }

    /* Return the device ID value */
    return touchIC;
}
uint8_t GT9157_TS_DetectTouch (uint16_t DeviceAddr)
{
    uint8_t ret = 1;
    // uint8_t  finger = 0;
    // uint8_t  point_data[11] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xff}; 
    // //GTP_I2C_Read (DeviceAddr, point_data, 11);

    // finger = point_data[2];//状态寄存器数据
    // if (finger == 0x00) {	//没有数据，退出
    //     ret = 0;
    // }

    return ret;
}
void GT9157_TS_Start (uint16_t DeviceAddr)
{

}
void GT9157_TS_ClearIT (uint16_t DeviceAddr)
{
    /* Clear the global TS IT source */
    GTP_I2C_Write (DeviceAddr, end_cmd, 3);
}
void GT9157_TS_GetXY (uint16_t DeviceAddr, uint16_t * X, uint16_t * Y)
{
    uint32_t uldataXYZ;
	uint8_t finger;
	uint8_t touch_num;
    uint8_t point_data[11] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF};
    GTP_I2C_Read (DeviceAddr, point_data, 11); //10字节寄存器加2字节地址
    finger = point_data[GTP_ADDR_LENGTH];//状态寄存器数据

    if (finger == 0x00) {	//没有数据，退出
        return;
    }
    if ((finger & 0x80) == 0) { //判断buffer status位
        goto exit_work_func;//坐标未就绪，数据无效
    }
    touch_num = finger & 0x0f;//坐标点数
    if (touch_num > GTP_MAX_TOUCH) {
        goto exit_work_func;//大于最大支持点数，错误退出
    }

    uldataXYZ = (point_data[5] << 24) | (point_data[4] << 16) | (point_data[7] << 8) | (point_data[6] << 0);
    *X = (uldataXYZ >> 16) & 0x0000FFFF;
    *Y = (uldataXYZ) & 0x0000FFFF;
exit_work_func: {
        GTP_I2C_Write(DeviceAddr, end_cmd, 3);
    }
}
void GT9157_TS_EnableIT (uint16_t DeviceAddr)
{
    //   IOE_ITConfig();
    IOE_ITGT9157Config();
    /* Enable global interrupt */
    // GT9157_EnableGlobalIT ();
}
void GT9157_TS_DisableIT (uint16_t DeviceAddr)
{
    /* Disable global interrupt */
    // GT9157_DisableGlobalIT ();
}
uint8_t GT9157_TS_ITStatus (uint16_t DeviceAddr)
{
    /* Return TS interrupts status */
    //   return(stmpe811_ReadGITStatus(DeviceAddr, STMPE811_TS_IT));
	return 0;
}
// static uint8_t GT9157_GetInstance (uint16_t DeviceAddr)
// {
//     uint8_t idx = 0;

//     /* Check all the registered instances */
//     for (idx = 0; idx < GTP_MAX_TOUCH ; idx ++) {
//         if (GT9157[idx] == DeviceAddr) {
//             return idx;
//         }
//     }

//     return 0xFF;
// }
static void GTP_I2C_Write (uint8_t DeviceAddr, uint8_t * buf, int32_t len)
{
    uint16_t MemAddress;
    // GTP_DEBUG_FUNC();
    MemAddress = ((uint16_t)buf[0]) << 8 | buf[1];
    IOE16_Write(DeviceAddr, MemAddress, &buf[2], len - GTP_ADDR_LENGTH);
}
static void GTP_I2C_Read (uint8_t DeviceAddr, uint8_t * buf, int32_t len)
{
    uint16_t MemAddress;
    // GTP_DEBUG_FUNC();
    MemAddress = ((uint16_t)buf[0]) << 8 | buf[1];
    IOE16_Read(DeviceAddr, MemAddress, &buf[2], len - GTP_ADDR_LENGTH);
}
// static void GT9157_EnableGlobalIT ()
// {
//     // GPIO_InitTypeDef GPIO_InitStruct;
//     // /*Configure GPIO pin : PtPin */
//     // GPIO_InitStruct.Pin = CTP_INT_Pin;
//     // GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
//     // GPIO_InitStruct.Pull = GPIO_NOPULL;
//     // HAL_GPIO_Init (CTP_INT_GPIO_Port, &GPIO_InitStruct);
//     // /* 配置中断优先级 */
//     // // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//     // /*使能中断*/
//     // HAL_NVIC_SetPriority (EXTI15_10_IRQn, 1, 1);
//     // HAL_NVIC_EnableIRQ (EXTI15_10_IRQn);
// }
// static void GT9157_DisableGlobalIT ()
// {
//     // GPIO_InitTypeDef GPIO_InitStruct;
//     // /*Configure GPIO pin : PtPin */
//     // GPIO_InitStruct.Pin = CTP_INT_Pin;
//     // GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
//     // GPIO_InitStruct.Pull = GPIO_NOPULL;
//     // HAL_GPIO_Init (CTP_INT_GPIO_Port, &GPIO_InitStruct);
//     // /* 配置中断优先级 */
//     // // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//     // /*使能中断*/
//     // HAL_NVIC_SetPriority (EXTI15_10_IRQn, 1, 1);
//     // HAL_NVIC_EnableIRQ (EXTI15_10_IRQn);
// }
