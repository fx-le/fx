//
// Created by FangJianRu on 2025/10/29.
//
// PID计算函数
#include "pid.h"
void PID::reset(void) {
    err_sum_ = 0;
    last_err_ = 0;
    last_dout_ = 0;
    output_ = 0;
    pout_ = 0;
    iout_ = 0;
    dout_ = 0;
}
float PID::calc(float ref, float fdb) {
    ref_ = ref;
    fdb_ = fdb;
    err_ = ref_ - fdb_;
    //P
    pout_ = kp_ * err_;
    //I
    err_sum_ += err_;
    iout_ = ki_ * err_sum_;
    if (iout_ > i_max_) {
        iout_ = i_max_;
        err_sum_ = i_max_ / ki_;
    } else if (iout_ < -i_max_) {
        iout_ = -i_max_;
        err_sum_ = -i_max_ / ki_;
    }
    //D
    float d_err = err_ - last_err_;
    dout_ = d_filter_k_ * (kd_ * d_err) + (1 - d_filter_k_) * last_dout_;
    last_dout_ = dout_;
    last_err_ = err_;
    output_ = pout_ + iout_ + dout_;
    if (output_ > out_max_) {
        output_ = out_max_;
    } else if (output_ < -out_max_) {
        output_ = -out_max_;
    }
    return output_;
}