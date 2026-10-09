#ifndef CAR_CONTROL_H
#define CAR_CONTROL_H

#include "car_defs.h"

// 设置自动控制请求
void car_control_set_auto(Car* car, MoveMode mode, int speed);

// 设置手动控制请求
void car_control_set_manual(Car* car, MoveMode mode, int speed);

// 释放手动控制
void car_control_release_manual(Car* car);

// 获取当前生效的控制源（手动优先）
CtrlSource car_control_get_active(const Car* car);

// 控制源枚举转大写字符串
const char* car_control_src_str(CtrlSource c);

// 运动模式枚举转大写字符串
const char* car_control_mode_str(MoveMode m);

#endif
#pragma once
