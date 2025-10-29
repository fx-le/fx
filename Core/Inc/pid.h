//
// Created by FangJianRu on 2025/10/29.
//

#ifndef LED10_1_PID_H
#define LED10_1_PID_H

#endif //LED10_1_PID_H
class PID {
public:
    PID(void) : PID(0, 0, 0, 0, 0) {}
    PID(float kp, float ki, float kd, float i_max, float out_max,
        float d_filter_k = 1);

    void reset(void);
    float calc(float ref, float fdb);

    float kp_, ki_, kd_, d_filter_k_;
    float i_max_, out_max_;
    float output_;

private:
    float ref_, fdb_;
    float err_, err_sum_, last_err_;
    float pout_, iout_, dout_, last_dout_;
};

PID::PID(float kp, float ki, float kd, float i_max, float out_max, float d_filter_k)
        : kp_(kp), ki_(ki), kd_(kd), i_max_(i_max), out_max_(out_max), d_filter_k_(d_filter_k),
          output_(0), ref_(0), fdb_(0), err_(0), err_sum_(0), last_err_(0),
          pout_(0), iout_(0), dout_(0), last_dout_(0) {
}

