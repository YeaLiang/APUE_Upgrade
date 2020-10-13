#UNIX 环境高级网络编程 (简称APUE)
## 第一章 UNIX 基础知识
### 第四节 列出指定目录的文件名

文档中出现的代码均会重新手敲一遍，后续可能会看时间补充下练习代码
因为文档代码依赖apue.h文件，我已经把相关用到的代码单独拎出来，一起放在工程里面，方便编译和学习

Blog主要分三部分
- 第一部分是代码，主要是自我学习和练习代码能力，可以直接运行，工程会同步更新到github上面
- 第二部分是注释，主要是描述工程中用到的一些不熟悉的结构体和头文件
- 第三部分是运行，主要是代码编译以及后面的运行实例结果

**代码**

```C++
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

using namespace std;

#define	MAXLINE	4096			/* max line length */

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
	exit(1);
}


/*
 * Fatal error unrelated to a system call.
 * Print a message and terminate.
 * 将致命的错误和系统调用关联起来
 * 打印错误信息并且终止程序
 */
void err_quit(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);          /*declared in stdarg.h*/
	err_doit(0, 0, fmt, ap);
	va_end(ap);
	exit(1);
}


int main(int argc,char* argv[])
{
    // 定义文件句柄指针
    DIR             *dp;
    // 定义存储子目录信息的结构体指针
    struct dirent   *dirp;

    if (argc != 2)
    {
        err_quit("usage: ls directory_name");
    }

    if (NULL == (dp = opendir(argv[1])))
    {
        err_sys("can't open %s.",argv[1]);
    }

    while (NULL != (dirp = readdir(dp)))
    {  
        //printf("%s\n",dirp->d_name);
        cout << "ino: " << dirp->d_ino << ",off: " << dirp->d_off
            << ",filetype: " << (int)dirp->d_type << ",namelen: " << dirp->d_reclen
            << ",filename: " << dirp->d_name << endl;
        
    }
    
    closedir(dp);

    return 0;
}
```

**注释**

struct dirent 结构体定义如下：
```C
struct dirent
{
#ifndef __USE_FILE_OFFSET64         
    __ino_t d_ino;
    __off_t d_off;
#else
    __ino64_t d_ino;
     __off64_t d_off;
#endif
    unsigned short int d_reclen;
    unsigned char d_type;
    char d_name[256];	
};
```
结构体说明：
__USE_FILE_OFFSET64  宏指的是当操作大文件的时候，才需要定义，否则即使用默认的32的偏移地址形式操作文件

d_ino: 索引节点号
d_off: 在目录文件中的偏移量
d_reclen: 文件名长度
d_type: 文件类型


**运行**
> 运行命令
> cd ../build
> make -j4
> cd ../bin
> ./ls /etc/sysconfig


