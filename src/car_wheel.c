#include <car_wheel.h>
#include <car_control.h>

void car_wheel_calc_vector(MoveMode mode, int speed, int out[4])
{
    // Ë³Ðò£º×óÇ°ÂÖ¡¢ÓÒÇ°ÂÖ¡¢×óºóÂÖ¡¢ÓÒºóÂÖ
    switch (mode) {
    case M_FORWARD:
        out[0] = speed; out[1] = speed; out[2] = speed; out[3] = speed;
        break;
    case M_BACKWARD:
        out[0] = -speed; out[1] = -speed; out[2] = -speed; out[3] = -speed;
        break;
    case M_LEFT:
        out[0] = -speed; out[1] = speed; out[2] = speed; out[3] = -speed;
        break;
    case M_RIGHT:
        out[0] = speed; out[1] = -speed; out[2] = -speed; out[3] = speed;
        break;
    case M_STOP:
    default:
        out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
        break;
    }
}

void car_wheel_update_target(Car* car)
{
    CtrlSource active = car_control_get_active(car);
    MoveMode mode = M_STOP;
    int speed = 0;

    if (active == CTRL_MANUAL) {
        mode = car->manual_req.mode;
        speed = car->manual_req.speed;
    }
    else if (active == CTRL_AUTO) {
        mode = car->auto_req.mode;
        speed = car->auto_req.speed;
    }

    car_wheel_calc_vector(mode, speed, car->wheel_target);
}

void car_wheel_step(Car* car)
{
    for (int i = 0; i < 4; i++) {
        int diff = car->wheel_target[i] - car->wheel_actual[i];
        int delta;

        if (diff > 20)       delta = 20;
        else if (diff < -20) delta = -20;
        else                delta = diff;

        car->wheel_actual[i] += delta;
    }
}
