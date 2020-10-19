#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>

using namespace std;

int main(int argc,char* argv[])
{
    cerr << "EACCESS: " << strerror(5616165) << endl;  /* define in string.h */
    errno = ENOENT;
    perror(argv[0]);    /* define in stdio.h */
    
    return 0;
}