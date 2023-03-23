#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>

int main()
{
	DIR *dir;
	struct dirent *elem;
	char path[20], name[10], pid[20];
	FILE *fp;
	int counter = 0, i, length;

	dir = opendir("/proc");	
	
	while ( ( elem = readdir(dir) ) != NULL )
	{
		strcpy(pid, elem->d_name);
		length = strlen(pid);
		for ( i = 0; i < length; ++i )
		{
			if ( !isdigit( elem->d_name[i] ) )
			{
				i = -1;
				break;
			}
		}
		if ( i == -1 ) continue;

		sprintf(path, "/proc/%s/comm", pid);
		fp = fopen(path, "r");
		fscanf(fp, "%s", name);
		if ( strstr(name, "genenv") != NULL ) counter++;
	}

	closedir(dir);	
	printf("%d\n", counter);

	return 0;
}
