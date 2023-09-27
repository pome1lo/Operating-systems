#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
	pid_t pid = getpid();
	printf("puzikov");
	for (short i = 1; i <= 10000; ++i)
	{
		printf("%d. PID = %d\n", i, pid);
		sleep(1);
	}
	
	exit(0);
}
//ps:		ps -p PID
// /proc:	cd proc/PID; ls -l