#include <stdio.h>
#include <stdlib.h>

void dfs( int* count, int ppid, char* buf )
{
	FILE *fp;
	int pid;
	
	sprintf( buf, "/proc/%d/task/%d/children", ppid, ppid );
	fp = fopen( buf, "r" );
	
	while ( fscanf( fp, "%d", &pid ) == 1 )
	{
		(*count)++;
		dfs( count, pid, buf );
	}
	
	fclose(fp);
}

int main( int argc, char* argv[] )
{
	int count = 1;
	char buf[40];
	
	dfs( &count, atoi( argv[1] ), buf );
	printf("%d\n", count);
	
	return 0;
}