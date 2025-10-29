//
// Created by FangJianRu on 2025/10/23.
//

#include "m3508.h"
M3508_Motor Motor(19.2f);
extern CAN_TxHeaderTypeDef tx_header;
extern uint8_t tx_data[8];
float linearMapping(int in, int in_min, int in_max, float out_min, float out_max) {
    return out_min + (in - in_min) * ((out_max - out_min) / (in_max - in_min));
    }

void M3508_Motor::canRxMsgCallback(const uint8_t rx_data[8]) {
    last_ecd_angle_ = ecd_angle_;
    int ecd_angle = (rx_data[0] << 8) | rx_data[1];
    ecd_angle_ = linearMapping(ecd_angle, 0, 8191, 0.0, 360.0);
    delta_ecd_angle_ = ecd_angle_ - last_ecd_angle_;
    if (delta_ecd_angle_ > 180.0) delta_ecd_angle_ -= 360.0;
    else if (delta_ecd_angle_ < -180.0) delta_ecd_angle_ += 360.0;
    delta_angle_ = delta_ecd_angle_ / ratio_;
    angle_ += delta_angle_;
    int rotate_speed = (rx_data[2] << 8) | rx_data[3];
    rotate_speed_ = (float)rotate_speed*6.0f;
    int current = (rx_data[4] << 8) | rx_data[5];
    current_ = linearMapping(current, -16384, 16384, -20, 20);
    temp_ = rx_data[6];
    }

void M3508_Motor::SetPosition(float target_position, float feedforward_speed, float feedforward_intensity) {
    target_angle_ = target_position;
    feedforward_speed_ = feedforward_speed;
    feedforward_intensity_ = feedforward_intensity;
    control_method_ = POSITION_SPEED;
}

void M3508_Motor::SetSpeed(float target_speed, float feedforward_intensity) {
    target_speed_ = target_speed;
    feedforward_intensity_ = feedforward_intensity;
    control_method_ = SPEED;
}

void M3508_Motor::SetIntensity(float intensity) {
    output_intensity_ = intensity;
    control_method_ = TORQUE;
}

// 处理函数 - 根据不同的控制模式计算输出
void M3508_Motor::handle(void) {
    switch (control_method_) {
        // 转矩控制
        case TORQUE:
            break;
        // 速度控制：速度环PID + 前馈
        case SPEED:
            output_intensity_ = spid_.calc(target_speed_, fdb_speed_) + feedforward_intensity_;
            break;
        // 位置-速度双环控制
        case POSITION_SPEED:
            float speed_command = ppid_.calc(target_angle_, fdb_angle_) + feedforward_speed_;
            output_intensity_ = spid_.calc(speed_command, fdb_speed_) + feedforward_intensity_;
            break;
    }
}