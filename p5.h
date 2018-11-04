#ifindef P5_H
#define P5_H



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




#endif
