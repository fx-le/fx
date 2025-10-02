//
// Created by FangJianRu on 2025/10/2.
//
#include "tim.h"
uint8_t n=0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin==KEY_Pin){
        uint32_t arr_value=__HAL_TIM_GetAutoreload(&htim1)+1;
        uint32_t brightness=(__HAL_TIM_GetCompare(&htim1,TIM_CHANNEL_2)+100)%arr_value;
                __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,brightness);
        n++;
    }
}