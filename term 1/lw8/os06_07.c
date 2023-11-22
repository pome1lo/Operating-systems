#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sched.h>
#define KB (1024)
#define IC 256

int main() {
	pid_t pid = getpid();
	printf("OS06_06 PID %d\n", pid);
	
	int countItems = IC / sizeof(int);

	int* mem1 = malloc(1024 * 256);
	printf("mem1(1024*256) = %p\n", mem1);
    for (int i = 0; i<countItems; i++) 
    {
      mem1[i] = i;
    }
	
	sleep(60 * 60 * 60);
	
	exit(0);
}