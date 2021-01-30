#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[])
{
     pid_t tid;
     tid = syscall(186);
     printf("tid : %d\n",tid);
     tid = syscall(SYS_tgkill, getpid(), tid, SIGHUP);
     printf("tid : %d ...\n",tid);
     while(1);
}
