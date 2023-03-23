#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler( int signum )
{
	exit(0);
}

int main()
{
	printf( "%d\n", getpid() );
	fclose( stdout );
	
	daemon( 0, 0 );
	signal( SIGURG, sig_handler );
	while ( 1 ) {}
	
	return 0;
}