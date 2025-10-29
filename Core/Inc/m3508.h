//
// Created by FangJianRu on 2025/10/23.
//

#ifndef LED10_1_M3508_H
#define LED10_1_M3508_H

#endif //LED10_1_M3508_H

#include "main.h"
#include "pid.h"
class M3508_Motor {
private:
    const float ratio_;             //电机减速比
    float angle_ = 0.f;                //deg输出端累计转动角度
    float delta_angle_ = 0.f;        //deg输出端新转动的角度
    float ecd_angle_ = 0.f;            //deg当前电机编码器角度
    float last_ecd_angle_ = 0.f;        //deg上次电机编码器角度
    float delta_ecd_angle_ = 0.f;    //deg编码器端新转动的角度
    float rotate_speed_ = 0.f;        //dps反馈转子转速
    float current_ = 0.f;            //A反馈转矩电流
    float temp_ = 0.f;                //℃反馈电机温度
public:
    explicit M3508_Motor(const float ratio) : ratio_(ratio) {};
    void canRxMsgCallback(const uint8_t rx_data[8]);
    PID spid_, ppid_;
    float target_angle_, fdb_angle_;
    float target_speed_, fdb_speed_, feedforward_speed_;
    float feedforward_intensity_, output_intensity_;
    enum {
        TORQUE,
        SPEED,
        POSITION_SPEED,
    } control_method_;
    void SetPosition(float target_position, float feedforward_speed, float feedforward_intensity);
    void SetSpeed(float target_speed, float feedforward_intensity);
    void SetIntensity(float intensity);
    void handle(void);
};