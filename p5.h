#ifndef P5_H
#define P5_H

#include <sys/shm.h>
#include <sys/ipc.h>

#define KEY 6789 /* logical clock */
#define SKEY 7771 /* request path */

int rshm_id;
/*void* rshm_msg;*/

int shm_id;
/*void* shm_msg;*/

typedef struct resource_desc{
	int process;
	char * request;
	char * allocation;
	char * release;
	int max_claims;	
	
} Resource;

#endif
