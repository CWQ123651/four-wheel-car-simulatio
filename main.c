#include <stdio.h>
#include <string.h>
#include <car_defs.h>
#include <car_state.h>
#include <car_control.h>
#include <car_wheel.h>
#include <car_status.h>
#include <cmd_parser.h>

#define BUF_LEN 256
 char buf[BUF_LEN];
    
int main(void)
{
    Car car;
    car_state_init(&car);
   

    while (fgets(buf, BUF_LEN, stdin) != NULL) {
        // 去掉换行符
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') buf[len - 1] = '\0';

        ParsedCmd cmd = cmd_parse(buf);

        switch (cmd.type) {
        case CMD_QUIT:
            return 0;

        case CMD_START:
            car_state_start(&car);
            break;

        case CMD_EMERGENCY:
            car_state_emergency(&car);
            car_wheel_update_target(&car);
            break;

        case CMD_RESET:
            car_state_reset(&car);
            break;

        case CMD_STEP:
            if (car.sys_state == S_RUNNING) {
                car_wheel_step(&car);
            }
            break;

        case CMD_STATUS:
            car_status_dump(&car);
            break;

        case CMD_AUTO:
            if (car.sys_state != S_RUNNING) break;
            if (cmd.mode != M_STOP && (cmd.speed < 0 || cmd.speed > 100)) break;
            car_control_set_auto(&car, cmd.mode, cmd.speed);
            car_wheel_update_target(&car);
            break;

        case CMD_MANUAL:
            if (car.sys_state != S_RUNNING) break;
            if (cmd.mode != M_STOP && (cmd.speed < 0 || cmd.speed > 100)) break;
            car_control_set_manual(&car, cmd.mode, cmd.speed);
            car_wheel_update_target(&car);
            break;

        case CMD_MANUAL_RELEASE:
            if (car.sys_state != S_RUNNING) break;
            car_control_release_manual(&car);
            car_wheel_update_target(&car);
            break;

        default:
            // 未知命令直接忽略，不崩溃
            break;
        }
    }

    return 0;
}
