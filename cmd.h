/*
 * Copyright (c) 2019, jiejie <https://github.com/jiejieTop>
 * Copyright (c) 2020, hong54321 <https://github.com/hong54321>
 * Copyright (c) 2022, smartmx <smartmx@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-13     jiejie       the first version
 * 2020-03-06     jiejie       fix the hash algorithm bug
 * 2020-03-29     hong54321    update
 * 2022-04-01     smartmx      add gcc support
 *
 */
#ifndef _CMD_H_
#define _CMD_H_

#define CMD_HASH 0xb433e5c6

#if defined(__CC_ARM) || defined(__CLANG_ARM)   /* ARM Compiler */
    #define SECTION(x)                  __attribute__((section(x)))
    #define CMD_USED                    __attribute__((used))

#elif defined (__IAR_SYSTEMS_ICC__)             /* IAR Compiler */
    #define SECTION(x)                  @ x
    #define CMD_USED                    __root
#elif defined (__GNUC__)
    #define SECTION(x)                  __attribute__((section(x)))
    #define CMD_USED                    __attribute__((used))
#else
    #error "not supported tool chain..."
#endif


typedef void (*cmd_handler)(void);

typedef struct cmd
{
    const char     *cmd;
    const char     *cmd_mess;
    unsigned int    hash;
    cmd_handler     handler;
} cmd_t;

#define REGISTER_CMD(cmd, handler,desc)                         \
    const char _register_##cmd##_cmd[] = #cmd;                  \
    const char _register_##cmd##_desc[] = #desc;                \
    CMD_USED cmd_t _register_##cmd SECTION("CMDS")=             \
    {                                                           \
        _register_##cmd##_cmd,                                  \
        _register_##cmd##_desc,                                 \
        (unsigned int)CMD_HASH,                                 \
        (cmd_handler)&handler                                   \
    };

void cmd_init(void);
void cmd_parsing(char *str);

#endif

