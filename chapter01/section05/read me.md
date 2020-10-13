#UNIX 环境高级网络编程 (简称APUE)
## 第一章 UNIX 基础知识
### 第五节 拷贝指定文件

文档中出现的代码均会重新手敲一遍，后续可能会看时间补充下练习代码
因为文档代码依赖apue.h文件，我已经把相关用到的代码单独拎出来，一起放在工程里面，方便编译和学习

Blog主要分三部分
- 第一部分是代码，主要是自我学习和练习代码能力，可以直接运行，工程会同步更新到github上面
- 第二部分是注释，主要是描述工程中用到的一些不熟悉的结构体和头文件
- 第三部分是运行，主要是代码编译以及后面的运行实例结果

**代码**

```c++
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
using namespace std;

#define	MAXLINE	    4096			/* max line length */
#define	BUFFSIZE	4096

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

int main(int argc,char* argv[])
{
    int read_num = 0;
    char buf[BUFFSIZE] = {0};

    while ((read_num = read(STDIN_FILENO,buf,BUFFSIZE)) > 0)
    {
        if(write(STDOUT_FILENO,buf,read_num) != read_num)
        {
            err_sys("write error.");
        }
    }

    if (read_num < 0)
    {
        err_sys("read error,ret:%d",read_num);
    }

    return 0;
}
```

**注释**
`STDIN_FILENO：     标准输入流句柄`
`STDOUT_FILENO：    标准输出流句柄`

**运行**
> 运行命令
> cd ../build
> make -j4
> cd ../bin
> ./copyfile < /etc/passwd > ./usrpwd.info




[代码工程github地址](https://github.com/YeaLiang/APUE_Upgrade/tree/main/chapter01/section05)



**每日一句**
*有的人总说：已经晚了*
*实际上，现在是最好的时光。*
*对于一个真正有所追求的人来说，*
*生命的每个时期都是年轻的、即使的。*
**《人生永远没有太晚的开始》 ——摩西奶奶**