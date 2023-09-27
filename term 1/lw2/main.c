#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    pid_t pid = getpid();
    for (int i = 1; i <= 1000; i++) 
    {
        printf("PID: %d, сообщение: %d\n", pid, i); 
        printf(" PUZIKOV ");
        sleep(2);
    }
    return 0;
}
// gcc main.c -o app -std=c11
// ./app