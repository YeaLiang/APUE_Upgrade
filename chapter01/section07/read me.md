# UNIX 环境高级网络编程 (简称APUE)
## 第一章 UNIX 基础知识
### 第七节 错误处理

文档中出现的代码均会重新手敲一遍，后续可能会看时间补充下练习代码
因为文档代码依赖apue.h文件，我已经把相关用到的代码单独拎出来，一起放在工程里面，方便编译和学习

Blog主要分三部分
- 第一部分是代码，主要是自我学习和练习代码能力，可以直接运行，工程会同步更新到github上面
- 第二部分是注释，主要是描述工程中用到的一些不熟悉的结构体和头文件
- 第三部分是运行，主要是代码编译以及后面的运行实例结果

**代码**

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>

using namespace std;

int main(int argc,char* argv[])
{
    cerr << "EACCESS: " << strerror(EACCES) << endl;  /* define in string.h */
    errno = ENOENT;
    perror(argv[0]);    /* define in stdio.h */
    
    return 0;
} 
```
 
  
---
 
  
**注释**

> 该代码核心点在以下四个函数
> (1)、strerror
>> 原型: char *strerror(int errnum);
>> 作用: 将指定的整型错误码转换成字符串，并且通过返回值返回
>> 参数:  
>>> int errnum: 整型错误码，可通过errno(线程安全，thread-local variable) 获取
>> 返回值：
>>> 成功: 返回错误码对应的字符串提示
>>> 提示：返回"Unknown error errnum"
>  
> (2)、perror
>> 原型: void perror(const char *str);
>> 作用: 把一个描述性错误消息输出到标准错误 stderr。首先输出字符串 str，后跟一个冒号，然后是一个空格，然后是真正的错误信息
>> 参数: const char *str: 自定义错误输出，显示在原本的错误信息之前
>> 返回值: 无


**运行**
> 运行命令
> cd ../build
> make -j4
> cd ../bin
> ./copyfile
> ls
> pwd



[代码工程github地址](https://github.com/YeaLiang/APUE_Upgrade/tree/main/chapter01/section07)



**每日一句**
*与恶龙缠斗过久，*
*自身亦成为恶龙。*
*凝视深渊过久，*
*深渊将回以凝视。*
**　　　　　　　　《善与恶的彼岸》**
**　　　　　　　　　　　　——尼采**