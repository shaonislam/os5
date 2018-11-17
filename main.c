
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include "p5.h"


/*
oss:

	Shared Memory: 
		system data structures
		resource descriptors for each resource
			-request, allocation, release, max claims, instance of resource to process -(20 descriptors)
		logical clock
	
*/

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


	/*_________Setup shmMSG_________*/
	rshm_id = shmget(SKEY, sizeof(int)*2, IPC_CREAT | 0666);
	void* rshm;
	rshm = shmat(rshm_id, NULL, 0);
	int* shterm_time = rshm;
	


	/*_________Setup Shared Memory For Master Clock_________*/

        shm_id = shmget(KEY, sizeof(int)*2, IPC_CREAT | 0666);
        void* shm;
       	shm = shmat(shm_id, NULL, 0);
	
        /*_________PUT THE CLOCK IN SHARED MEMORY_________ */

        int*  master_clock = shm;
        int seconds = 0;
        int nanosec = 0;
        master_clock[0] = seconds;
        master_clock[1] = nanosec;


        /*_________Set Up Resource Descriptors_________*/

        Resource res[20];



	/*________Create a Child To Run________*/
	int live_children;
	pid_t child_pid;
	child_pid = fork();
	if (child_pid == 0)
	{
        	execlp("./user", "./user",(char *)NULL);
	}
	else
	{

	/*_________Increment System Clock_______*/
        /* Increment System Clock BY 100000 Nanoseconds */
        master_clock[1] = master_clock[1] + 100000;
        if (master_clock[1] > 999999999)
        {
                master_clock[1] = master_clock[1] %  1000000000;
                master_clock[0] = master_clock[0] + 1;
        }

	}
	

	wait(&child_pid);
		fprintf(stderr, "Child Exited\n");	

        /*______Clean Out Shared Memory_______*/
        shmctl(shm_id, IPC_RMID, NULL);
        shmctl(rshm_id, IPC_RMID, NULL);

	return 0;

}

