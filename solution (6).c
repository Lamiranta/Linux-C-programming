#include <stdio.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>

int main( int agrc, char* argv[] )
{
	int fds[2];
	char buf[4096];
	int i, rc, maxfd, sum = 0;
	fd_set watchset, inset;
	
	fds[0] = open( "in1", O_RDONLY | O_NONBLOCK );
	fds[1] = open( "in2", O_RDONLY | O_NONBLOCK );
	
	FD_ZERO( &watchset );
	FD_SET( fds[0], &watchset );
	FD_SET( fds[1], &watchset );
	
	maxfd = fds[0] > fds[1] ? fds[0] : fds[1];
	
	while ( FD_ISSET( fds[0], &watchset ) || FD_ISSET( fds[1], &watchset ) )
	{
		inset = watchset;
		select( maxfd + 1, &inset, NULL, NULL, NULL );
		
		for ( i = 0; i < 2; ++i )
		{
			if ( FD_ISSET( fds[i], &inset ) )
			{
				rc = read( fds[i], buf, sizeof( buf ) - 1 );
				if ( !rc )
				{
					close( fds[i] );
					FD_CLR( fds[i], &watchset );
				}
				else
				{
					buf[rc] = '\0';
					sum += atoi( buf );
				}
			}
		}
	}
	
	printf( "%d\n", sum );
	
	return 0;
}