/*
 * @Author: jiejie
 * @Github: https://github.com/jiejieTop
 * @Date: 2019-12-13 19:15:30
 * @LastEditTime: 2019-12-17 13:38:49
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

REGISTER_CMD(test1, test1_cmd,test1 demo);
REGISTER_CMD(test2, test2_cmd,test2 demo);
REGISTER_CMD(test3, test3_cmd,test3 demo);

int main(void)
{
    cmd_init();

    while (1)
    {
        cmd_parsing("_list");
        cmd_parsing("test1");
        cmd_parsing("test2");
        cmd_parsing("test3");
        delay(1000);
    }
    
    return 0;
}
