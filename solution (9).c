#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main( int argc, char* argv[] )
{
	int shmID1 = shmget( atoi( argv[1] ), 1000, 0666 );
	int shmID2 = shmget( atoi( argv[2] ), 1000, 0666 );
	int shmID3 = shmget( atoi( argv[1] ) / 2 + atoi( argv[2] ) / 2, 1000, IPC_CREAT | 0666 );
	
	int* shm1 = shmat( shmID1, NULL, 0 );
	int* shm2 = shmat( shmID2, NULL, 0 );
	int* shm3 = shmat( shmID3, NULL, 0 );
	
	int i, *it1 = shm1, *it2 = shm2, *it3 = shm3;
	
	for ( i = 0; i < 100; ++i )
	{
		*it3++ = *it1++ + *it2++;
	}
	
	printf( "%d\n", atoi( argv[1] ) / 2 + atoi( argv[2] ) / 2 );
	
	return 0;
}