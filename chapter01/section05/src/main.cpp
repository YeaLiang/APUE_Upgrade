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

/*

int main(void)
{
    int c = 0;
    while (EOF != (c = getc(stdin)))
    {
        if(putc(c,stdout) == EOF)
        {
            err_sys("output error.");
        }
    }

    if(ferror(stdin))
    {
        err_sys("input error.");
    }
    
    return 0;
}

*/