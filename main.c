
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <getopt.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>


void handle_terminate(int sig)
{
        fprintf(stderr, "Terminating due to 2 second program life span is over.\n");
        exit(1);
}



int main (int argc, char *argv[])
{
		
	srand((unsigned)time(NULL));
	FILE *fname;

	/*______Set up signal______*/
        signal(SIGALRM, handle_terminate);
        alarm(2);	



	/*_________Setup Shared Memory For Master Clock_________*/

	int shm_id;
        key_t key;
        void* shm;
        key = 6789;
        shm_id = shmget(key, sizeof(int)*2, IPC_CREAT | 0666);
        if (shm_id == -1)
        {
                perror("shmget");
                exit(1);
        }
        shm = shmat(shm_id, NULL, 0);



	return 0;
}
