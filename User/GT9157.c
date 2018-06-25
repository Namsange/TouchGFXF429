#include "GT9157.h"

#define  GTP_MAX_TOUCH     (5)
#define GTP_REG_VERSION    (0x8140)
#define GTP_READ_COOR_ADDR (0x814E)
uint8_t GT9157[GTP_MAX_TOUCH] = {0};

static uint8_t GT9157_GetInstance (uint16_t DeviceAddr);

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
    uint8_t instance;
    uint8_t empty;
    uint8_t * cfg_info;
    uint8_t cfg_info_len;
    uint8_t check_sum = 0;
    uint8_t cfg_num = 0x80FE - 0x8047 + 1 ;
    /* Check if device instance already exists */
    instance = GT9157_GetInstance (DeviceAddr);

    /* To prevent double initialization */
    if (instance == 0xFF) {
        /* Look for empty instance */
        empty = GT9157_GetInstance (0);

        if (empty < GTP_MAX_TOUCH) {
            /* Register the current device instance */
            GT9157[empty] = DeviceAddr;
            /* Initialize IO BUS layer */
            IOE_Init();
            /* Generate GT9157 Software reset */
            GT9157_Reset (DeviceAddr);
        }
    }

    cfg_info =  CTP_CFG_GT9157; //指向寄存器配置
    cfg_info_len = CFG_GROUP_LEN (CTP_CFG_GT9157); //计算配置表的大小
    memset (&config[GTP_ADDR_LENGTH], 0, GTP_CONFIG_MAX_LENGTH);
    memcpy (&config[GTP_ADDR_LENGTH], cfg_info, cfg_info_len);
    check_sum = 0;

    for (i = GTP_ADDR_LENGTH; i < cfg_num + GTP_ADDR_LENGTH; i++) {
        check_sum += config[i];
    }

    config[ cfg_num + GTP_ADDR_LENGTH] = (~check_sum) + 1; 	//checksum
    config[ cfg_num + GTP_ADDR_LENGTH + 1] =  1; 						//refresh 配置更新标志

    //写入配置信息
    for (retry = 0; retry < 5; retry++) {
        ret = GTP_I2C_Write (GTP_ADDRESS, config, cfg_num + GTP_ADDR_LENGTH + 2);

        if (ret > 0) {
            break;
        }
    }
}
void GT9157_Reset (uint16_t DeviceAddr)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    /*配置 INT引脚，下拉推挽输出，方便初始化 */
    GPIO_InitStruct.Pin = = CTP_INT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pull  = GPIO_PULLDOWN;       //设置为下拉，方便初始化
    HAL_GPIO_Init (GPIOD, &GPIO_InitStruct);
    /*初始化GT9157,rst为高电平，int为低电平，则gt9157的设备地址被配置为0xBA*/
    /*复位为低电平，为初始化做准备*/
    HAL_GPIO_WritePin (GPIOD, CTP_RST_Pin, GPIO_PIN_RESET);
    // GPIOD->BSRRH = CTP_RST_Pin;
    Delay (0x0FFFFF);
    /*拉高一段时间，进行初始化*/
    HAL_GPIO_WritePin (GPIOD, CTP_RST_Pin, GPIO_PIN_SET);
    // GPIOD->BSRRL = CTP_RST_Pin;
    Delay (0x0FFFFF);
    /*把INT引脚设置为浮空输入模式，以便接收触摸中断信号*/
    GPIO_InitStruct.Pin = CTP_INT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_Init (GPIOD, &GPIO_InitStruct);
}
uint16_t GT9157_ReadID (uint16_t DeviceAddr)
{
    uint16_t touchIC = 0;
    uint8_t buf[8] = {GTP_REG_VERSION >> 8, GTP_REG_VERSION & 0xff};    //寄存器地址
    GTP_I2C_Read (GTP_ADDRESS, buf, sizeof (buf));

    if (buf[5] == 0x00) {
        //GT911芯片
        if (buf[2] == '9' && buf[3] == '1' && buf[4] == '1') {
            touchIC = 0x0911;
        }
    }
    else {
        //GT9157芯片
        if (buf[2] == '9' && buf[3] == '1' && buf[4] == '5' && buf[5] == '7') {
            touchIC = 0x9157;
        }
    }

    /* Return the device ID value */
    return touchIC;
}
void GT9157_EnableGlobalIT (uint16_t DeviceAddr)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = CTP_INT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init (CTP_INT_GPIO_Port, &GPIO_InitStruct);
    /* 配置中断优先级 */
    // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /*使能中断*/
    HAL_NVIC_SetPriority (EXTI15_10_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ (EXTI15_10_IRQn);
}
void GT9157_DisableGlobalIT (uint16_t DeviceAddr)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = CTP_INT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init (CTP_INT_GPIO_Port, &GPIO_InitStruct);
    /* 配置中断优先级 */
    // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /*使能中断*/
    HAL_NVIC_SetPriority (EXTI15_10_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ (EXTI15_10_IRQn);
}

void stmpe811_EnableITSource (uint16_t DeviceAddr, uint8_t Source);
void stmpe811_DisableITSource (uint16_t DeviceAddr, uint8_t Source);
// void stmpe811_SetITPolarity(uint16_t DeviceAddr, uint8_t Polarity);
uint8_t stmpe811_ReadGITStatus (uint16_t DeviceAddr, uint8_t Source)
{
    /* Return the global IT source status */
    return ((IOE_Read (DeviceAddr, STMPE811_REG_INT_STA) & Source));
}
uint8_t GT9157_TS_DetectTouch (uint16_t DeviceAddr)
{
    uint8_t ret = 0;
    uint8_t  finger = 0;
    uint8_t  point_data[3] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF};
    GTP_I2C_Read (client_addr, point_data, 3);
    finger = point_data[GTP_ADDR_LENGTH];//状态寄存器数据

    if (finger != 0x00) {	//没有数据，退出
        ret = 1;
    }

    return ret;
}
void GT9157_TS_Start (uint16_t DeviceAddr)
{
    ;
}
void GT9157_TS_ClearIT (uint16_t DeviceAddr)
{
    uint8_t  end_cmd[3] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF, 0};
    /* Clear the global TS IT source */
    GTP_I2C_Write (client_addr, end_cmd, 3);
}
void GT9157_TS_GetXY (uint16_t DeviceAddr, uint16_t * X, uint16_t * Y)
{
    uint8_t ret = 0;
    uint32_t uldataXYZ;
    uint8_t  point_data[1 + 8 * GTP_MAX_TOUCH] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF};
    ret = GTP_I2C_Read (client_addr, point_data, 3); //10字节寄存器加2字节地址
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

    if (touch_num > 1) { //不止一个点
        uint8_t buf[8 * GTP_MAX_TOUCH] = { (GTP_READ_COOR_ADDR + 1) >> 8, (GTP_READ_COOR_ADDR + 1) & 0xff};
        ret = GTP_I2C_Read (client_addr, buf,  8 * touch_num);
        memcpy (&point_data[0], &buf[2], 8 * (touch_num - 1));	//复制其余点数的数据到point_data
    }

    /* Calculate positions values */
    uldataXYZ = (point_data[2] << 24) | (point_data[1] << 16) | (point_data[4] << 8) | (point_data[3] << 0);
    *X = (uldataXYZ >> 16) & 0x0000FFFF;
    *Y = (uldataXYZ) & 0x0000FFFF;
exit_work_func: {
        ret = GTP_I2C_Write (client_addr, end_cmd, 3);
    }
}
void GT9157_TS_EnableIT (uint16_t DeviceAddr)
{
    //   IOE_ITConfig();
    /* Enable global interrupt */
    GT9157_EnableGlobalIT (DeviceAddr);
}
void GT9157_TS_DisableIT (uint16_t DeviceAddr)
{
    /* Disable global interrupt */
    GT9157_DisableGlobalIT (DeviceAddr);
}
uint8_t GT9157_TS_ITStatus (uint16_t DeviceAddr)
{
    /* Return TS interrupts status */
    //   return(stmpe811_ReadGITStatus(DeviceAddr, STMPE811_TS_IT));
}
static uint8_t GT9157_GetInstance (uint16_t DeviceAddr)
{
    uint8_t idx = 0;

    /* Check all the registered instances */
    for (idx = 0; idx < GTP_MAX_TOUCH ; idx ++) {
        if (GT9157[idx] == DeviceAddr) {
            return idx;
        }
    }

    return 0xFF;
}