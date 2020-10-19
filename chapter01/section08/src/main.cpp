#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

int main(int argc,char* argv[])
{
   cout << "uid = " << getuid() << ",gid = " << getgid() << endl;
}