#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main( int agrc, char* argv[] )
{
	int i = 0;
	struct hostent* host = gethostbyname( argv[1] );
	
	while( host->h_addr_list[i] != NULL )
	{
		struct in_addr* addr = (struct in_addr*) host->h_addr_list[i];
		printf( "%s\n", inet_ntoa( *addr ) );
		i++;
	}
	
	return 0;
}
