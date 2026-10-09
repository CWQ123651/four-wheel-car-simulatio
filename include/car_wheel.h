#ifndef CAR_WHEEL_H
#define CAR_WHEEL_H

#include "car_defs.h"

// 根据当前生效控制，重新计算四轮目标速度
void car_wheel_update_target(Car* car);

// 执行一次 step，实际速度向目标逼近
void car_wheel_step(Car* car);

// 根据运动模式+速度，计算四轮速度向量
void car_wheel_calc_vector(MoveMode mode, int speed, int out[4]);

#endif
#pragma once
