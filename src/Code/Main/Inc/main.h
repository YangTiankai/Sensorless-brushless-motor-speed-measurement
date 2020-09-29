#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"
#include "bsp.h"
#include "device.h"
#include "tools.h"
#include "host.h"
#include "control.h"

// #define ROCKER_RANGE                (660.0f)     //摇杆范围为-660 ~ +660
// #define MANUAL_MAX_SPEED_PULSE      10000   //手动速度模式下的编码器最快转速，单位为5ms内的脉冲数

#define UART_DMA_RX_SIZE    (128)

typedef struct
{
    int32_t ms;
    int32_t us;
} time_stamp_t;

typedef struct
{
    uint8_t nextout;
    uint16_t data[MAX_LIST];
} list_t, *p_list_t;


typedef struct
{
    int32_t ms;
    int32_t cyclepack;
    int32_t cycle100ms;
} CLOCK;



extern CLOCK clock;
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
extern TIM_HandleTypeDef htim6;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_uart4_tx;
extern DMA_HandleTypeDef hdma_uart5_rx;
extern DMA_HandleTypeDef hdma_uart5_tx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern DMA_HandleTypeDef hdma_usart6_rx;
extern DMA_HandleTypeDef hdma_usart6_tx;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;

void cycle_100ms_callback(void);
void cycle_pack_callback(void);
void MY_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */


