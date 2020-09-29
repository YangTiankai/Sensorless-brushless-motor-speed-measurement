
#include "gpio.h"


/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/


/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
     PA6   ------> S_TIM13_CH1
     PA7   ------> S_TIM14_CH1
     PB4   ------> S_TIM3_CH1
*/
void MX_GPIO_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();


    HAL_GPIO_WritePin(WIFI_MD0_GPIO_Port, WIFI_MD0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(WIFI_MD1_GPIO_Port, WIFI_MD1_Pin, GPIO_PIN_SET);

    GPIO_InitStruct.Pin = WIFI_MD0_Pin  | WIFI_MD1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);



    // GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_8;
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);    

    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);    
    HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);    
    HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 2);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);    
    HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 3);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    // HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 1);
    // HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);    

}



