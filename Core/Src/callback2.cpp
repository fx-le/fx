//
// Created by FangJianRu on 2025/10/2.
//
#include "main.h"
#include "usart.h"
extern uint8_t rx_msg[10];
extern uint8_t tx_msg[10];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef*huart){
    if(huart==&huart7)
    {
        if(rx_msg[0]=='R')
        {
            HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,GPIO_PIN_RESET);
        }
        else if(rx_msg[0]=='M')
        {
            HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,GPIO_PIN_SET);
        }
        /*HAL_UART_Receive_IT(&huart7,rx_msg,10);*/
        for(int8_t i=0;i<10;i++)tx_msg[i]=rx_msg[i];
        HAL_UART_Transmit(&huart7,tx_msg,10,1000);
    }
}
