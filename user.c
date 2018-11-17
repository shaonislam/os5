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
#include <signal.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>
#include "p5.h"

#define CONSTANT 4
#define MAX 7


int ran(int bound)
{
	int num = (rand() % (bound+1) + 1);

	return num;
}


void handle_terminate(int sig)
{
        fprintf(stderr, "Terminating due to 2 second program life span is over.\n");
	shmctl(shm_id, IPC_RMID, NULL);
        shmctl(rshm_id, IPC_RMID, NULL); 
        exit(1);
}

int main (int argc, char *argv[])
{	

        /*______Set up signal______*/
        signal(SIGALRM, handle_terminate);
        alarm(2);

	srand(time(0));


	/*_________Setup Shared Memory For Master Clock_________*/
       
	 shm_id = shmget(KEY, sizeof(int)*2, IPC_CREAT | 0666);
        void* shm;
       	shm = shmat(shm_id, NULL, 0);
	int* master_clock = shm;

       
	 /*_________Setup shmMSG_________*/
        
	rshm_id = shmget(SKEY, sizeof(int)*2, IPC_CREAT | 0666);
        void* rshm;
        rshm = shmat(rshm_id, NULL, 0);
        int* shterm_time = rshm;

	
	/*_________Setup Semaphore_________*/

	sem_t *sem; /*synch semaphore*/
	sem = sem_open("thisSem", O_CREAT|O_EXCL, 0644, 10);
	sem_unlink("thisSem");

	
	int max_claims[19];
	int i;
	for (i = 0; i < 21; i++)	
 	{
		max_claims[i] = ran(MAX);
	}

	int bound = ran(CONSTANT);

	fprintf(stderr, "PROCESS %ld with Bound: %d\n", (long)getpid(), bound); 

	/*_________Check System Clock Until Deadline _________*/

	/*______ENTERING CRITICAL SECTION_____*/

	sem_wait(sem);



	sem_destroy(sem);
	return 0;
}
