#include <stdio.h>
#include <string.h>

int main( int agrc, char* argv[] )
{
	FILE *fp;
	char buf[40], c;
	int count = 0;
	
	sprintf( buf, "%s %s", argv[1], argv[2] );
	fp = popen( buf, "r" );
	
	while ( ( c = fgetc( fp ) ) != EOF )
	{
		count += ( c == '0' );
	}
	
	printf( "%d\n", count );
	pclose( fp );
	
	return 0;
}