
#include "tim.h"



TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim6;

TIM_OC_InitTypeDef sConfigOC;

__weak void MY_SYSCLK_Callback(void)
{
    return;
}


//系统定时器
//100us一次中断
void MX_TIM6_Init(void)
{
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim6.Instance = TIM6;
    htim6.Init.Prescaler = 84 - 1;
    htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim6.Init.Period = 1000 - 1;
    htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
    {
        Error_Handler(__FILE__, __LINE__);
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
    {
        Error_Handler(__FILE__, __LINE__);
    }
    HAL_TIM_Base_Start_IT(&htim6);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
 {
    if(htim->Instance == TIM3)
    {
        GPIO_InitTypeDef GPIO_InitStruct;

        __HAL_RCC_TIM3_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;

        GPIO_InitStruct.Pin = GPIO_PIN_7;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        // GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        // GPIO_InitStruct.Pull = GPIO_PULLUP;
        // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        // GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;

        // GPIO_InitStruct.Pin = GPIO_PIN_6;
        // HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);        
    }
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{    
    if(tim_baseHandle->Instance==TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
    }
}
