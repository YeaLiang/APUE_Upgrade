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