#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )
{
	FILE *fp;
	char path[20], line[256] = {'\0'};
	int pid, ppid = atoi(argv[1]), tgid;

	printf("%d\n", ppid);
	
	while ( ppid != 1 )
	{
		pid = ppid;
		tgid = 0;
		sprintf(path, "/proc/%d/status", pid);
		fp = fopen(path, "r");
		
		while ( pid == ppid || tgid == 0 )
		{
			fgets(line, 256, fp);
			if ( strstr(line, "Tgid:") != NULL )
			{
				sscanf(line, "Tgid:\t%d\n", &tgid);
				if ( pid != tgid ) printf("%d\n", tgid);
			}
			if ( strstr(line, "PPid:") != NULL )
			{
				sscanf(line, "PPid:\t%d\n", &ppid);
				printf("%d\n", ppid);
			}
		}

		fclose(fp);
	}

	return 0;
}