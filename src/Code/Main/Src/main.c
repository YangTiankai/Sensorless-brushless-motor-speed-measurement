
#include "main.h"
#include "math.h"



CLOCK clock = {0};
state_t state = {0};
uint8_t buff[256] = {0};
uint16_t len = 0;
uint8_t anobuff[256] = {0};
uint16_t anolen = 0;

time_stamp_t lasttime0 = {0};
time_stamp_t lasttime1 = {0};
time_stamp_t lasttime2 = {0};
time_stamp_t lasttime3 = {0};

list_t list0 = {0};
list_t list1 = {0};
list_t list2 = {0};
list_t list3 = {0};

int cnt0 = 0;
int cnt1 = 0;
int cnt2 = 0;
int cnt3 = 0;

float rpm0_10hz = 0;
float rpm1_10hz = 0;
float rpm2_10hz = 0;
float rpm3_10hz = 0;

void push_data(p_list_t plist, uint16_t data)
{
    plist->data[plist->nextout] = data;
    plist->nextout++;
    if(plist->nextout >= MAX_LIST)
    {
        plist->nextout = 0;
    }
}

float us_to_rpm(int us)
{
    return 1.0e6 * 60.0 / 7.0 / (float)us;
}

float cnt_to_rpm(int cnt)
{
    return (float)cnt * 10.0 / 7.0 * 60.0;
}

float list_avg(p_list_t plist)
{
    // int i;
    // float sum = 0;
    // for(i = 0; i <= MAX_LIST - 1; i++)
    // {
    //     sum += plist->data[i];
    // }
    // return sum / (float)MAX_LIST;


    float cur;
    int i, j;
    int length = MAX_LIST;

    float buff[MAX_LIST];
    for(i = 0; i <= MAX_LIST - 1; i++)
    {
        buff[i] = plist->data[i];
    }

    for (i = 1; i < length; i++)
    {
        cur = buff[i];    //待排序元素
        for (j = i - 1; j >= 0 && buff[j] > cur; j--)
        {
            buff[j + 1] = buff[j];
        }
        buff[j + 1] = cur;
    }

    return buff[LIST_LEFT];
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == UART4)
    {
        __HAL_UART_CLEAR_OREFLAG(&huart4);
    }   
    else if(huart->Instance == USART6)
    {
        __HAL_UART_CLEAR_OREFLAG(&huart6);
    } 
}

inline void MY_SYSCLK_Callback(void)
{
    clock.ms++;
    clock.cycle100ms++;
    clock.cyclepack++;
}

void smalldelay(void)
{
    volatile int i = 0;
    i++;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_0)
    {
        if( (GPIOA->IDR & (1 << 0) ) != 0 )
        {
            smalldelay();
            if( (GPIOA->IDR & (1 << 0) ) != 0 )
            {
                int cur_ms = clock.ms;
                int cur_us = TIM6->CNT;
                uint16_t data = 0;
                data = (clock.ms - lasttime0.ms) * 1000 + (cur_us - lasttime0.us);
                if(data > MIN_CYCLE_US)
                {
                    lasttime0.ms = cur_ms;
                    lasttime0.us = cur_us;
                    if( fabs( rpm0_10hz - us_to_rpm(data) ) < 10000 )
                    {
                        push_data(&list0, data);
                    }
                    cnt0++;
                }
            }
        }
    }
    else if(GPIO_Pin == GPIO_PIN_1)
    {
        if( (GPIOA->IDR & (1 << 1) ) != 0 )
        {
            smalldelay();
            if( (GPIOA->IDR & (1 << 1) ) != 0 )
            {
                int cur_ms = clock.ms;
                int cur_us = TIM6->CNT;
                uint16_t data = 0;
                data = (clock.ms - lasttime1.ms) * 1000 + (cur_us - lasttime1.us);
                if(data > MIN_CYCLE_US)
                {
                    lasttime1.ms = cur_ms;
                    lasttime1.us = cur_us;
                    if( fabs( rpm1_10hz - us_to_rpm(data) ) < 10000 )
                    {
                        push_data(&list1, data);
                    }
                    
                    cnt1++;
                }
            }
        }
    }
    else if(GPIO_Pin == GPIO_PIN_2)
    {
        if( (GPIOA->IDR & (1 << 2) ) != 0 )
        {
            smalldelay();
            if( (GPIOA->IDR & (1 << 2) ) != 0 )
            {  
                int cur_ms = clock.ms;
                int cur_us = TIM6->CNT;
                uint16_t data = 0;
                data = (clock.ms - lasttime2.ms) * 1000 + (cur_us - lasttime2.us);
                if(data > MIN_CYCLE_US)
                {
                    lasttime2.ms = cur_ms;
                    lasttime2.us = cur_us;
                    if( fabs( rpm2_10hz - us_to_rpm(data) ) < 10000 )
                    {
                        push_data(&list2, data);
                    }
                    cnt2++;
                }
            }
        }
    }
    else if(GPIO_Pin == GPIO_PIN_3)
    {
        if( (GPIOA->IDR & (1 << 3) ) != 0 )
        {
            smalldelay();
            if( (GPIOA->IDR & (1 << 3) ) != 0 )
            {
                int cur_ms = clock.ms;
                int cur_us = TIM6->CNT;
                uint16_t data = 0;
                data = (clock.ms - lasttime3.ms) * 1000 + (cur_us - lasttime3.us);
                if(data > MIN_CYCLE_US)
                {
                    lasttime3.ms = cur_ms;
                    lasttime3.us = cur_us;
                    if( fabs( rpm3_10hz - us_to_rpm(data) ) < 10000 )
                    {
                        push_data(&list3, data);
                    }
                    cnt3++;
                }
                
            }
        }
    }
}

int main(void)
{    
    HAL_Init();
    SystemClock_Config();

    LED_Core_Init();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_IWDG_Init();
    MX_USART1_UART_Init();  //核心板输出
    // MX_USART2_UART_Init();  //无线串口
    // MX_USART3_UART_Init();
    // MX_UART5_Init();        //接收机
    // MX_USART6_UART_Init();  //上位机

    MX_UART4_Init();//上位机

    MX_TIM6_Init();


    while(1)
    {
        if(clock.cycle100ms >= 100)
        {
            cycle_100ms_callback();
            clock.cycle100ms = 0;            
        }
        if(clock.cyclepack >= CYCLE_PACK_MS)
        {
            cycle_pack_callback();
            clock.cyclepack = 0;            
        }        
    }
}

float checkreal(float data, float real, float lastdata)
{
    if(real < 1000)
    {
        return 0;
    }
    else
    {
        // if(fabs(data - lastdata) < 5000)
        {
            return data;
        }
        // else
        // {
        //     return lastdata;
        // }
    }

     
    // if(fabs(data - real) > 180.0)
    // {
    //     return real;
    // }
    // else
    // {
    //     return data;
    // }
    
}


inline void cycle_pack_callback(void)
{
    static float lastrpm0 = 0;
    static float lastrpm1 = 0;
    static float lastrpm2 = 0;
    static float lastrpm3 = 0;

    uint16_t anodata[10];

    state.id = 1;
    state.cycle_ms = 10;
    state.ms = clock.ms;
    state.us = TIM6->CNT;


    float rpm0 = us_to_rpm( list_avg(&list0) );
    float rpm1 = us_to_rpm( list_avg(&list1) );
    float rpm2 = us_to_rpm( list_avg(&list2) );
    float rpm3 = us_to_rpm( list_avg(&list3) );

    

    state.pulse0 = checkreal(rpm0, rpm0_10hz, lastrpm0);
    state.pulse1 = checkreal(rpm1, rpm1_10hz, lastrpm1);
    state.pulse2 = checkreal(rpm2, rpm2_10hz, lastrpm2);
    state.pulse3 = checkreal(rpm3, rpm3_10hz, lastrpm3);

    lastrpm0 = state.pulse0;
    lastrpm1 = state.pulse1;
    lastrpm2 = state.pulse2;
    lastrpm3 = state.pulse3;


    anodata[0] = state.pulse0;
    anodata[1] = state.pulse1;
    anodata[2] = state.pulse2;
    anodata[3] = state.pulse3;

    ANOPrintS16(1, anodata, 4, anobuff, &anolen);

    // gen_state_string(&state, buff, &len);
    gen_state_pack(&state, buff, &len);

    HAL_UART_Transmit_DMA(&huart4, buff, len);
    HAL_UART_Transmit_DMA(&huart1, anobuff, anolen);
    return;
}


inline void cycle_100ms_callback(void)
{
    rpm0_10hz = cnt_to_rpm(cnt0);
    rpm1_10hz = cnt_to_rpm(cnt1);
    rpm2_10hz = cnt_to_rpm(cnt2);
    rpm3_10hz = cnt_to_rpm(cnt3);

    cnt0 = 0;
    cnt1 = 0;
    cnt2 = 0;
    cnt3 = 0;

    LED_Core_Turn();
    HAL_IWDG_Refresh(&hiwdg);
    return;
}


