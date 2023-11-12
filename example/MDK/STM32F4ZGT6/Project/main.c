#include "stm32f4xx.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "cmd.h"

void test1_cmd(void)
{
    printf("test1_cmd\n");
}REGISTER_CMD(test1, test1_cmd,test1 demo);

void test2_cmd(void)
{
    printf("test2_cmd\n");
}REGISTER_CMD(test2, test2_cmd,test2 demo);

void test3_cmd(void)
{
    printf("test3_cmd\n");
}REGISTER_CMD(test3, test3_cmd,test3 demo);



int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(115200);
    delay_init(168);

    cmd_init();
    cmd_parsing("_list");
    cmd_parsing("test1");
    cmd_parsing("test2");
    cmd_parsing("test3");
    while (1)
    {
    }
}
