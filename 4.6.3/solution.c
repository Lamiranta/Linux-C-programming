#include <stdio.h>
#include <signal.h>

int count[2] = { 0, 0 };

void usr_hdl_1( int signum )
{
	count[0]++;
}

void usr_hdl_2( int signum )
{
	count[1]++;
}

void term_hdl( int signum )
{
	printf( "%d %d\n", count[0], count[1] );
	exit(0);
}

int main()
{
	signal( SIGUSR1, usr_hdl_1 );
	signal( SIGUSR2, usr_hdl_2 );
	signal( SIGTERM, term_hdl );
	
	while ( 1 ) {}
	
	return 0;
}
