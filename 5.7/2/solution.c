#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct sockaddr_in local;

int main( int agrc, char* argv[] )
{
	int s = socket( AF_INET, SOCK_DGRAM, 0 );
	char buf[10001];
	
	inet_aton( "127.0.0.1", &local.sin_addr );
	local.sin_port = htons( atoi( argv[1] ) );
	local.sin_family = AF_INET;
	
	if ( bind( s, (struct sockaddr*) &local, sizeof( local ) ) == 0 )
	{
		while ( 1 )
		{
			memset( buf, 0, 10001 );
			read( s, buf, 10001 );
			if ( !strncmp( buf, "OFF\n", 4 ) )
				break;
			else
				printf("%s\n", buf);
		}
	}
	
	return 0;
}
