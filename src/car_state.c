#include <car_state.h>

void car_state_init(Car* car)
{
    car->sys_state = S_IDLE;
    car->auto_req.valid = false;
    car->manual_req.valid = false;
    for (int i = 0; i < 4; i++) {
        car->wheel_actual[i] = 0;
        car->wheel_target[i] = 0;
    }
}

void car_state_start(Car* car)
{
    if (car->sys_state != S_EMERGENCY) {
        car->sys_state = S_RUNNING;
    }
}

void car_state_emergency(Car* car)
{
    car->sys_state = S_EMERGENCY;
    // 急停直接清零实际速度，不经过 step
    for (int i = 0; i < 4; i++) {
        car->wheel_actual[i] = 0;
    }
}

void car_state_reset(Car* car)
{
    car->sys_state = S_IDLE;
    car->auto_req.valid = false;
    car->manual_req.valid = false;
    for (int i = 0; i < 4; i++) {
        car->wheel_actual[i] = 0;
        car->wheel_target[i] = 0;
    }
}

const char* car_state_str(SysState s)
{
    switch (s) {
    case S_IDLE:      return "IDLE";
    case S_RUNNING:   return "RUNNING";
    case S_EMERGENCY: return "EMERGENCY";
    default:          return "IDLE";
    }
}
