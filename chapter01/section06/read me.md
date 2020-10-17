# UNIX 环境高级网络编程 (简称APUE)
## 第一章 UNIX 基础知识
### 第五节 拷贝指定文件

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
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

#define	MAXLINE	    4096			/* max line length */

/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag".
 */
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
	char	buf[MAXLINE];

	vsnprintf(buf, MAXLINE-1, fmt, ap);
	if (errnoflag)
    {
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s",strerror(error));
    }
	strcat(buf, "\n");  /* declared in string.h*/
	fflush(stdout);		/* in case stdout and stderr are the same */
	fputs(buf, stderr);
	fflush(NULL);		/* flushes all stdio output streams */
}

/*
 * Fatal error related to a system call.
 * Print a message and terminate.
 * 将致命的错误和系统调用关联起来
 * 打印错误信息并且终止程序
 */
void err_sys(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	exit(1);        /*declared in stdlib.h*/
}

/*
 * Nonfatal error related to a system call.
 * Print a message and return.
 */
void err_ret(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
}

int main(int argc,char* argv[])
{
    char buf[MAXLINE] = {0};

    pid_t process_id = 0;
    int status = 0;
    cout << "]> ";
    while (fgets(buf,MAXLINE,stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = 0;
        }
        
        if ((process_id = fork()) < 0)
        {
            err_sys("fork error,errno:%d",errno);
        }
        else
        if (process_id == 0) /* child process */
        {
            execlp(buf,buf,(char*)0);
            err_ret("couldn't execute: %s",buf);
            exit(127);
        }
        
        /* parent */
        if ((process_id == waitpid(process_id,&status,0)) < 0)
        {
            err_sys("waitpid error");
        }

        cout << "]> ";
    }
    
    return 0;
}
```

---

**注释**

> 该代码核心点在以下四个函数
> (1)、fgets
>> 原型: char *fgets(char *s, int size, FILE *stream);
>> 作用: 按行从指定的流中读取n-1个字符或者读取到换行符(\n) 为止
>> 参数:  
>>> char *s: 用于存储从输入流中读取到的字符流，需调用方提供存储空间
>>> int size: 指定从输入流中读取多少个字符(包括最后的换行符)
>>> FILE *stream: 指向FILE对象的指针，标识了可以读取的文件流
>> 返回值：
>>> 成功: 则返回与第一个参数相同的内容，遇到文件末尾或者没有读取到内容，也返回空指针
>>> 失败：返回空指针
>  
> (2)、fork
>> 原型: pid_t fork(void);
>> 作用: 创建一个新进程，新进程会复制当前进程的所有内容，包括进程内存各种代码段，数据段以及调用堆栈信息
>> 参数: 无
>> 返回值: 该函数回返回两次，因为，新进程复制了当前进程的函数调用堆栈，所以，在新进程当中该函数也会返回
>>> 主进程：成功时返回创建的新进程的进程id， 失败时返回-1，并且将错误码存储在errno中，
>>> 子进程：成功时，返回 0，失败则没有子进程
> 
> (3)、execlp
>> 原型: int execlp(const char *file, const char *arg, ...);
>> 作用: 从环境变量中查找文件名与file参数一致的文件，然后执行调用，并将参数args传入
>> 参数: 
>>> const char *file: 可执行文件名
>>> const char *arg: 执行文件参数
>>> ...: 不定长参数，说明可以有多个参数传入，但是最后一个参数必须以空指针结尾
> 
> (4)、waitpid
>> 原型: pid_t waitpid(pid_t pid,int * status,int options);
>> 作用: 暂停当前调用进程并且等待指定的进程状态变更，然后返回
>> 参数: 
>>> pid_t pid: 
>>>> pid = -1: 任何一个子进程状态变更，该函数均会返回，此时，函数功能和wait()类似
>>>> pid > 0 : 等待子进程id为pid的状态变更，然后函数返回。
>>>> pid = 0 : 与调用进程组id相同的任意子进程状态变更均回返回
>>>> pid < -1: 进程组id为pid的绝对值的任意子进程状态变更均回返回
>>> int * status: 用来存储子进程返回的状态变更信息
>>> int options: 设置等待状态，可为阻塞等待，也可为非阻塞回收
>> 返回值： 成功则返回状态变更的子进程id，失败则返回-1


**运行**
> 运行命令
> cd ../build
> make -j4
> cd ../bin
> ./copyfile
> ls
> pwd




[代码工程github地址](https://github.com/YeaLiang/APUE_Upgrade/tree/main/chapter01/section06)



**每日一句**
*与恶龙缠斗过久，*
*自身亦成为恶龙。*
*凝视深渊过久，*
*深渊将回以凝视。*
**　　　　　　　　《善与恶的彼岸》**
**　　　　　　　　　　　　——尼采**