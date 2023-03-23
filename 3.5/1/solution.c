#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char pid[10], path[20];
	int ppid;
	
	strcpy(path, "/proc/");
	sprintf(pid, "%d", getpid());
	strcat(path, pid);
	strcat(path, "/stat");
	
	FILE* stat_file = fopen(path, "r");
	fscanf(stat_file, "%*d %*s %*c %d", &ppid);
	
	printf("%d\n", ppid);
}
