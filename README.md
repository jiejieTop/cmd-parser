# cmd-parser

一个非常简单好用的命令解析器...

这个命令解析器有什么用？？

> 简单来说，我希望我的开发板，可以通过命令执行一些处理，比如说我用串口发一个命令`A`，开发板就执行`A`的一些处理，或者，在调试某些`AT`模组的时候，当我收到模组返回的一些指令后，自动执行一些处理。当然，还有其他的地方可以用得上的，兄弟们自行挖掘！！欢迎提交**pr**与点个**star**~

## 使用方法

1. 注册命令

在工程中的任意位置均可调用（在函数外）

```js
REGISTER_CMD(test1, test1_cmd);
```

2. cmd初始化

```js
cmd_init();
```

3. 解析命令

```js
cmd_parsing("test1");
```

## 特色

- 用户无需关心命令的存储区域与大小，由编译器静态分配。
- 加入哈希算法，时间复杂度从O(n*m)变为O(n)。
- 命令忽略大小写。
- 非常易用与非常简洁的代码（不足150行）。

## 注意事项

- 本代码目前只支持`MDK`与`IAR`的编译器，对于`gcc`尚未移植，欢迎参与贡献


## test.c
```js
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
