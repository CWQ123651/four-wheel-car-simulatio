#include <car_status.h>
#include <car_state.h>
#include <car_control.h>
#include <stdio.h>

void car_status_dump(const Car* car)
{
    CtrlSource active = car_control_get_active(car);

    // 第1行：STATE
    printf("STATE %s\n", car_state_str(car->sys_state));

    // 第2行：CONTROL
    printf("CONTROL %s\n", car_control_src_str(active));

    // 第3行：AUTO
    if (car->auto_req.valid) {
        printf("AUTO %s", car_control_mode_str(car->auto_req.mode));
        if (car->auto_req.mode != M_STOP) {
            printf(" %d", car->auto_req.speed);
        }
        printf("\n");
    }
    else {
        printf("AUTO NONE\n");
    }

    // 第4行：MANUAL
    if (car->manual_req.valid) {
        printf("MANUAL %s", car_control_mode_str(car->manual_req.mode));
        if (car->manual_req.mode != M_STOP) {
            printf(" %d", car->manual_req.speed);
        }
        printf("\n");
    }
    else {
        printf("MANUAL NONE\n");
    }

    // 第5行：TARGET
    MoveMode t_mode = M_STOP;
    int t_speed = 0;
    if (active == CTRL_MANUAL) {
        t_mode = car->manual_req.mode;
        t_speed = car->manual_req.speed;
    }
    else if (active == CTRL_AUTO) {
        t_mode = car->auto_req.mode;
        t_speed = car->auto_req.speed;
    }
    printf("TARGET %s", car_control_mode_str(t_mode));
    if (t_mode != M_STOP) {
        printf(" %d", t_speed);
    }
    printf("\n");

    // 第6行：WHEELS
    printf("WHEELS %d %d %d %d\n",
        car->wheel_actual[0],
        car->wheel_actual[1],
        car->wheel_actual[2],
        car->wheel_actual[3]);
}
