#ifndef CMD_PARSER_H
#define CMD_PARSER_H

#include "car_defs.h"

// 命令类型枚举
typedef enum {
    CMD_UNKNOWN,
    CMD_QUIT,
    CMD_START,
    CMD_STEP,
    CMD_EMERGENCY,
    CMD_RESET,
    CMD_STATUS,
    CMD_AUTO,
    CMD_MANUAL,
    CMD_MANUAL_RELEASE
} CmdType;

// 解析后的结构化命令
typedef struct {
    CmdType type;
    MoveMode mode;   // auto/manual 命令时有效
    int speed;       // auto/manual 非 stop 时有效
} ParsedCmd;

// 解析一行输入字符串
ParsedCmd cmd_parse(const char* line);

#endif
#pragma once
