/*
Shaon Islam
user.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include "p5.h"

#define CONSTANT 4
#define MAX 7


int ran(int bound)
{
	int num = (rand() % (bound+1) + 1);

	return num;
}


int main (int argc, char *argv[])
{	
	srand(time(0));


	/*_________Setup Shared Memory For Master Clock_________*/
        shm_id = shmget(KEY, sizeof(int)*2, IPC_CREAT | 0666);
        void* shm;
       	shm = shmat(shm_id, NULL, 0);
	int* master_clock = shm;




	
	int max_claims[19];
	int i;
	for (i = 0; i < 21; i++)	
 	{
		max_claims[i] = ran(MAX);
	}

	int bound = ran(CONSTANT);

	fprintf(stderr, "PROCESS %ld with Bound: %d\n", (long)getpid(), bound); 




	return 0;
}
