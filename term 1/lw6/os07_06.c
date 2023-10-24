#include <stdio.h>

#include <stdlib.h>

#include <sys/types.h>

#include <unistd.h>

#include <pthread.h>



pthread_mutex_t mx;



void* A(void* arg)

{

	printf("------------Thread A is started-----------\n");

	for (int i = 1; i < 90; i++)

	{

		usleep(100000); printf("Thread A: %d\n", i);

		if (i == 30)

		{

			pthread_mutex_lock(&mx);

		}

		if (i == 60)

		{

			pthread_mutex_unlock(&mx);

		}

	}

	

	printf("------------Thread A is finished-----------\n");

	pthread_exit("Child thread A");

}



void* B(void* arg)

{

	printf("------------Thread B is started-----------\n");

	for (int i = 1; i < 90; i++)

	{

		usleep(100000); printf("Thread B: %d\n", i);

		if (i == 30)

		{

			pthread_mutex_lock(&mx);

		}

		if (i == 60)

		{

			pthread_mutex_unlock(&mx);

		}

	}

	printf("------------Thread B is finished-----------\n");

	pthread_exit("Child thread B");

}



int main()

{

	pthread_mutex_init(&mx, NULL);

	pthread_t a_th1, a_th2;

	void* r_th1, *r_th2;

	pid_t pid = getpid();



	printf("Main: pid = %d \n", pid);



	int res1 = pthread_create(&a_th1, NULL, A, NULL);

	int res2 = pthread_create(&a_th2, NULL, B, NULL);



	for (int i = 1; i < 90; i++)

	{

		usleep(100000);

		printf("Main: %d \n", i);

		if (i == 30)

		{

			pthread_mutex_lock(&mx);

		}

		if (i == 60)

		{

			pthread_mutex_unlock(&mx);

		}

	}



	int status1 = pthread_join(&a_th1, (void**)&r_th1);

	int status2 = pthread_join(&a_th2, (void**)&r_th2);

	pthread_mutex_destroy(&mx);

	exit(0);

}