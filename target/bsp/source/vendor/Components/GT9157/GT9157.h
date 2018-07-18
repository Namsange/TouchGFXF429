#ifndef _GT9157_H_
#define _GT9157_H_

#include "stm32f4xx.h"
#include "../target/bsp/source/vendor/Components/Common/ts.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CFG_GROUP_LEN(p_cfg_grp)  (sizeof(p_cfg_grp) / sizeof(p_cfg_grp[0]))
#define GTP_CONFIG_MAX_LENGTH 240
#define GTP_ADDR_LENGTH       2

#define GT9157_ID             0x9157

extern TS_DrvTypeDef GT9157_ts_drv;

extern void IOE16_Write (uint8_t Addr, uint16_t Reg, uint8_t * Value, uint16_t Size);
extern void IOE16_Read (uint8_t Addr, uint16_t Reg, uint8_t * Value, uint16_t Size);
extern void IOE_Init (void);
extern void HAL_Delay (uint32_t);
extern void IOE_ITGT9157Config (void);
extern void BSP_GT9157_IO_Reset (void);
void GT9157_Init (uint16_t DeviceAddr);
uint16_t GT9157_ReadID (uint16_t DeviceAddr);
void GT9157_Reset (uint16_t DeviceAddr);
void GT9157_TS_Start (uint16_t DeviceAddr);
uint8_t GT9157_TS_DetectTouch (uint16_t DeviceAddr);
void GT9157_TS_GetXY (uint16_t DeviceAddr, uint16_t * X, uint16_t * Y);
void GT9157_TS_EnableIT (uint16_t DeviceAddr);
void GT9157_TS_ClearIT (uint16_t DeviceAddr);
uint8_t GT9157_TS_ITStatus (uint16_t DeviceAddr);
void GT9157_TS_DisableIT (uint16_t DeviceAddr);

#ifdef __cplusplus
}
#endif

#endif /* _GT9157_H_ */

