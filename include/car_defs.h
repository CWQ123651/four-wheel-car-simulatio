#ifndef CAR_DEFS_H
#define CAR_DEFS_H

#include <stdbool.h>

// 系统状态
typedef enum {
    S_IDLE,
    S_RUNNING,
    S_EMERGENCY
} SysState;

// 运动模式
typedef enum {
    M_NONE,
    M_FORWARD,
    M_BACKWARD,
    M_LEFT,
    M_RIGHT,
    M_STOP
} MoveMode;

// 控制来源
typedef enum {
    CTRL_NONE,
    CTRL_AUTO,
    CTRL_MANUAL
} CtrlSource;

// 一条控制请求（auto / manual 共用结构）
typedef struct {
    bool valid;
    MoveMode mode;
    int speed;
} ControlReq;

// 小车整体状态
typedef struct {
    SysState sys_state;
    ControlReq auto_req;
    ControlReq manual_req;
    int wheel_actual[4];   // 顺序：左前、右前、左后、右后
    int wheel_target[4];
} Car;

#endif
