/*
 * @Author: jiejie
 * @Github: https://github.com/jiejieTop
 * @Date: 2019-12-13 10:47:30
 * @LastEditTime: 2019-12-13 19:23:32
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */
#include "cmd.h"

static cmd_t *_cmd_begin, *_cmd_end;

static void _cmd_init(const void *begin, const void *end)
{
    _cmd_begin = (cmd_t*) begin;
    _cmd_end = (cmd_t*) end;
}

static cmd_t* _get_next_cmd(cmd_t *cmd)
{
    unsigned int *ptr;
    ptr = (unsigned int*) (cmd + 1);
    while ((*ptr == 0) && ((unsigned int*)ptr < (unsigned int*) _cmd_end))
        ptr ++;

    return (cmd_t*) ptr;
}

static int _cmd_match(const char *str, const char *cmd)
{
    while (*str && (*str == *cmd)) {
        ++str;
        ++cmd;
    }
    
    return *str - *cmd;
}

void cmd_init(void)
{

#if defined(__CC_ARM) || defined(__CLANG_ARM)          /* ARM C Compiler */
    extern const int CMDS$$Base;
    extern const int CMDS$$Limit;
    _cmd_init(&CMDS$$Base, &CMDS$$Limit);
#elif defined (__ICCARM__) || defined(__ICCRX__)      /* for IAR Compiler */
    _cmd_init(__section_begin("CMDS"), __section_end("CMDS"));
#endif

}

void cmd_parsing(char *str)
{
    cmd_t *index;

    for (index = _cmd_begin; index < _cmd_end; index = _get_next_cmd(index)) {
        if (_cmd_match(str, index->cmd) == 0) {
            index->handler();
        }
    }
}


