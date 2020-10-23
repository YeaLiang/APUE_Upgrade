#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
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

static void sig_int(int);     /* our signal-catching function */

int main(int argc,char* argv[])
{
    char buf[MAXLINE] = {0};

    pid_t process_id = 0;
    int status = 0;

    if (signal(SIGINT,sig_int) == SIG_ERR)
    {
        err_sys("signal error");
    }
    

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

void sig_int(int signum)
{
    cout << "intercept\n" << endl;
}