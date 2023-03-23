#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

struct sockaddr_in local;

int comp( const void* elem1, const void* elem2 )
{
    char f = *( (char*) elem1 );
    char s = *( (char*) elem2 );
    if (f < s) return 1;
    if (f > s) return -1;
    return 0;
}

int main( int agrc, char* argv[] )
{
	int cs, ss = socket( AF_INET, SOCK_STREAM, 0 );
	char buf[10001];
	
	inet_aton( "127.0.0.1", &local.sin_addr );
	local.sin_port = htons( atoi( argv[1] ) );
	local.sin_family = AF_INET;
	
	bind( ss, (struct sockaddr*) &local, sizeof( local ) );
	listen( ss, 1 );
	cs = accept( ss, NULL, NULL );
	
	while( 1 )
	{
		read( cs, buf, 10001 );
		if ( strncmp( buf, "OFF", 3 ) == 0 )
			break;
			
		qsort( buf, strlen( buf ), 1, comp );
		write( cs, buf, strlen( buf ) + 1 );
		memset( buf, 0, 10001 );
	}
	
	close( cs );
	
	return 0;
}