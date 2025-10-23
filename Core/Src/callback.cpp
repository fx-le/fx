//
// Created by FangJianRu on 2025/10/23.
//
#include "can.h"
#include "gpio.h"
#include "m3508.h"
#include "main.h"
#include "tim.h"

extern CAN_RxHeaderTypeDef rx_header;
extern CAN_TxHeaderTypeDef tx_header;
extern uint8_t tx_data[8];
extern uint8_t rx_data[8];
extern uint32_t can_tx_mail_box_;
extern M3508_Motor Motor;
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
    if (hcan->Instance == CAN1) {
        //读包，获取header和data
        HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rx_header, rx_data);
        //自定义函数，将rx_data解析为电机信息
        if (rx_header.StdId == 0x201) {
            Motor.canRxMsgCallback(rx_data);
        }
    }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if (htim->Instance == htim6.Instance) {
        //发包
        tx_data[2] = 0xC0;
        HAL_CAN_AddTxMessage(&hcan1, &tx_header, tx_data, &can_tx_mail_box_);
    }
}