#ifndef CAR_STATE_H
#define CAR_STATE_H

#include "car_defs.h"

// 初始化小车全部状态
void car_state_init(Car* car);

// 从待机进入运行状态
void car_state_start(Car* car);

// 进入急停状态
void car_state_emergency(Car* car);

// 复位到待机状态
void car_state_reset(Car* car);

// 状态枚举转大写字符串
const char* car_state_str(SysState s);

#endif

