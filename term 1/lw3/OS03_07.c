#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
///mnt/d/files/university/3 course/1 term/OS/lw3

int main()
{
    char* const argv[] = { "ps", "-ef", 0 };    // массив параметров

    execv("./05_1.out", argv);               
    for (int i = 1; i <= 100; ++i)
    {
        printf("%d. PID = %d [OS03_07]\n", i, getpid());
        sleep(1);
    }
    exit(0);
}