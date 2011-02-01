#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t child_pid;
	
	child_pid = fork();
	if (child_pid < 0)
	{
		perror ("Error during fork");
	}
	else if (child_pid == 0)	/*This is child process*/
	{
		printf ("This is a child process.\n");
		exit (0);
	}
	printf ("This is a parent process.\n");
	return 0;
}
