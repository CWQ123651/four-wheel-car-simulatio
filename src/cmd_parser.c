#include <cmd_parser.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static MoveMode str_to_mode(const char* s)
{
    if (strcmp(s, "forward") == 0)  return M_FORWARD;
    if (strcmp(s, "backward") == 0) return M_BACKWARD;
    if (strcmp(s, "left") == 0)     return M_LEFT;
    if (strcmp(s, "right") == 0)    return M_RIGHT;
    if (strcmp(s, "stop") == 0)     return M_STOP;
    return M_NONE;
}

ParsedCmd cmd_parse(const char* line)
{
    ParsedCmd cmd = { CMD_UNKNOWN, M_NONE, 0 };
    // 数组加大+初始清零+sscanf限制最大读取长度
    char cmd_str[128] = { 0 }, arg1[128] = { 0 }, arg2[128] = { 0 };
    int n = sscanf(line, "%127s %127s %127s", cmd_str, arg1, arg2);

    if (n <= 0) return cmd;
    // ... 后面的判断逻辑保持不变


    if (strcmp(cmd_str, "quit") == 0) {
        cmd.type = CMD_QUIT;
    }
    else if (strcmp(cmd_str, "start") == 0) {
        cmd.type = CMD_START;
    }
    else if (strcmp(cmd_str, "step") == 0) {
        cmd.type = CMD_STEP;
    }
    else if (strcmp(cmd_str, "emergency") == 0) {
        cmd.type = CMD_EMERGENCY;
    }
    else if (strcmp(cmd_str, "reset") == 0) {
        cmd.type = CMD_RESET;
    }
    else if (strcmp(cmd_str, "status") == 0) {
        cmd.type = CMD_STATUS;
    }
    else if (strcmp(cmd_str, "auto") == 0) {
        MoveMode m = str_to_mode(arg1);
        if (m == M_NONE) return cmd;
        cmd.type = CMD_AUTO;
        cmd.mode = m;
        if (m != M_STOP && n >= 3) {
            cmd.speed = atoi(arg2);
        }
    }
    else if (strcmp(cmd_str, "manual") == 0) {
        if (strcmp(arg1, "release") == 0) {
            cmd.type = CMD_MANUAL_RELEASE;
        }
        else {
            MoveMode m = str_to_mode(arg1);
            if (m == M_NONE) return cmd;
            cmd.type = CMD_MANUAL;
            cmd.mode = m;
            if (m != M_STOP && n >= 3) {
                cmd.speed = atoi(arg2);
            }
        }
    }

    return cmd;
}
