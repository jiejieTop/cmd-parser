/*
 * @Author: jiejie
 * @Github: https://github.com/jiejieTop
 * @Date: 2019-12-13 19:15:30
 * @LastEditTime: 2019-12-13 19:20:41
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */
#include "cmd.h"

void test1_cmd(void)
{
    printf("test1_cmd\n");
}

void test2_cmd(void)
{
    printf("test2_cmd\n");
}

void test3_cmd(void)
{
    printf("test3_cmd\n");
}

REGISTER_CMD(test1, test1_cmd);
REGISTER_CMD(test2, test2_cmd);
REGISTER_CMD(test3, test3_cmd);

int main(void)
{
    cmd_init();

    while (1)
    {
        cmd_parsing("test1");
        cmd_parsing("test2");
        cmd_parsing("test3");
    }
    
    return 0;
}
