![](https://img.shields.io/badge/build-passing-brightgreen.svg)
[![license](https://img.shields.io/badge/license-Apache-blue.svg)](https://github.com/jiejieTop/cmd-parser/blob/master/LICENSE)
![](https://img.shields.io/badge/platform-MDK|IAR-orange.svg)

# cmd-parser

一个非常简单好用的命令解析器...

这个命令解析器有什么用？？

> 简单来说，我希望我的开发板，可以通过命令执行一些处理，比如说我用串口发一个命令`A`，开发板就执行`A`的一些处理，或者，在调试某些`AT`模组的时候，当我收到模组返回的一些指令后，自动执行一些处理。当然，还有其他的地方可以用得上的，兄弟们自行挖掘！！欢迎提交**pr**与点个**star**~

## 问题

欢迎以 [GitHub Issues](https://github.com/jiejieTop/mqttclient/issues) 的形式提交问题和bug报告

## 版权和许可

cmd-parser 遵循 [Apache License v2.0](https://github.com/jiejieTop/mqttclient/blob/master/LICENSE) 开源协议。鼓励代码共享和尊重原作者的著作权，可以自由的使用、修改源代码，也可以将修改后的代码作为开源或闭源软件发布，**但必须保留原作者版权声明**。

## MDK和IAR编译器使用方法

1. 注册命令

在工程中的任意位置均可调用（在函数外）

```c
REGISTER_CMD(test1, test1_cmd);
```

2. cmd初始化

```c
cmd_init();
```

3. 解析命令

```c
cmd_parsing("test1");
```

## GCC编译器使用方法

GCC工程需要在工程的ld文件中找到非零变量的初始化链接代码，将下面的代码粘贴到最后面即可

```c
. = ALIGN(4);
PROVIDE( CMDS_Base = . );
KEEP(*(CMDS))
PROVIDE( CMDS_Limit = . );
. = ALIGN(4);
```

例如：

```c
.data :
{
    . = ALIGN(4); 
    PROVIDE(_data_vma = .);
    *(.gnu.linkonce.r.*)
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    . = ALIGN(8);
    PROVIDE( __global_pointer$ = . + 0x800 );
    *(.sdata .sdata.*)
    *(.gnu.linkonce.s.*)
    . = ALIGN(8);
    *(.srodata.cst16)
    *(.srodata.cst8)
    *(.srodata.cst4)
    *(.srodata.cst2)
    *(.srodata .srodata.*)
    . = ALIGN(4);
    
    /* this section is for cmd parser */
    PROVIDE( CMDS_Base = . );
    KEEP(*(CMDS))
    PROVIDE( CMDS_Limit = . );
    . = ALIGN(4);
    
    PROVIDE( _edata = .);
} >RAM AT>FLASH

```

剩余步骤和上一节**MDK和IAR编译器使用方法**一致。

## 特色

- 用户无需关心命令的存储区域与大小，由编译器静态分配。
- 加入哈希算法超快速匹配命令，时间复杂度从O(n*m)变为O(n)。
- 命令支持忽略大小写。
- 非常易用与非常简洁的代码（不足150行）。

## test.c
```c
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
```
