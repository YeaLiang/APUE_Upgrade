# UNIX 环境高级网络编程 (简称APUE)
## 第一章 UNIX 基础知识
### 第八节 用户标识

文档中出现的代码均会重新手敲一遍，后续可能会看时间补充下练习代码
因为文档代码依赖apue.h文件，我已经把相关用到的代码单独拎出来，一起放在工程里面，方便编译和学习

Blog主要分三部分
- 第一部分是代码，主要是自我学习和练习代码能力，可以直接运行，工程会同步更新到github上面
- 第二部分是注释，主要是描述工程中用到的一些不熟悉的结构体和头文件
- 第三部分是运行，主要是代码编译以及后面的运行实例结果

---

**代码**

```cpp
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

int main(int argc,char* argv[])
{
   cout << "uid = " << getuid() << ",gid = " << getgid() << endl;
}
```
 
  
---
 
  
**注释**

> 该代码核心点在以下两个函数
> (1) getuid
>> 原型: uid_t getuid(void);
>> 作用: 用来获取执行当前进程的用户识别码。
>> 参数: 无
>> 返回值：返回执行当前进程的用户识别码
>  
> (2)、getgid
>> 原型: gid_t getgid(void);
>> 作用: 用来获取执行当前进程的组识别码。
>> 参数: 无
>> 返回值: 返回执行当前进程的组识别码

用户识别码的对应关系可以在 /etc/passwd 中查看
组识别码对应关系可以在 /etc/group 中查看

  
---
 

**运行**
> 运行命令
> cd ../build
> make -j4
> cd ../bin
> ./usrinfo


[代码工程github地址](https://github.com/YeaLiang/APUE_Upgrade/tree/main/chapter01/section08)

  
---
 

**每日一句**
*张华考上了研究生，*
*李萍自主创业，*
*我当上了技术工人：*
*我们都有美好的前途*
**　　　　　　　　《新华字典》(第12版)**
