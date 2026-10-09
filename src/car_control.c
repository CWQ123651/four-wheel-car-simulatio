#include <car_control.h>

void car_control_set_auto(Car* car, MoveMode mode, int speed)
{
    car->auto_req.valid = true;
    car->auto_req.mode = mode;
    car->auto_req.speed = speed;
}

void car_control_set_manual(Car* car, MoveMode mode, int speed)
{
    car->manual_req.valid = true;
    car->manual_req.mode = mode;
    car->manual_req.speed = speed;
}

void car_control_release_manual(Car* car)
{
    car->manual_req.valid = false;
}

CtrlSource car_control_get_active(const Car* car)
{
    // 核心规则：手动控制优先级高于自动
    if (car->manual_req.valid) {
        return CTRL_MANUAL;
    }
    else if (car->auto_req.valid) {
        return CTRL_AUTO;
    }
    else {
        return CTRL_NONE;
    }
}

const char* car_control_src_str(CtrlSource c)
{
    switch (c) {
    case CTRL_NONE:   return "NONE";
    case CTRL_AUTO:   return "AUTO";
    case CTRL_MANUAL: return "MANUAL";
    default:          return "NONE";
    }
}

const char* car_control_mode_str(MoveMode m)
{
    switch (m) {
    case M_FORWARD:  return "FORWARD";
    case M_BACKWARD: return "BACKWARD";
    case M_LEFT:     return "LEFT";
    case M_RIGHT:    return "RIGHT";
    case M_STOP:     return "STOP";
    case M_NONE:     return "NONE";
    default:         return "NONE";
    }
}
