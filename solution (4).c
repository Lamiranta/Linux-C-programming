#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("%d\n", getpid());
	fclose(stdout);
	daemon(0, 0);
	sleep(1000);
	return 0;
}