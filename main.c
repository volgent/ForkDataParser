#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

extern int getMessage (int write_fd);

struct Data			/*TODO: extern structure declaration*/
{
	char symb;
	int val;
};

int main(int argc, char **argv)
{
	pid_t child_pid;
	int pipe_ids[2];
	int rv;
	int i;
	struct Data dat2;
	struct timeval tv;
	fd_set rfds;
	
	rv = pipe(pipe_ids);
	if (rv != 0)	
	{
		perror ("Error during pipe call");
		return EXIT_FAILURE;
	}
	child_pid = fork();
	if (child_pid < 0)
	{
		perror ("Error during fork");
		return EXIT_FAILURE;
	}
	else if (child_pid == 0)	/*This is child process*/
	{
		rv = getMessage(pipe_ids[1]);
		if (rv == EXIT_FAILURE)
		{
			perror ("Error during getMessage");
		}
		printf ("Child process: now exiting.\n");
		exit (EXIT_SUCCESS);
	}
	
	FD_ZERO (&rfds);			/*Will watch pipe for new data*/
	FD_SET(pipe_ids[0], &rfds);
	
	tv.tv_sec = 1;				/*Wait for 1 second*/
	tv.tv_usec = 0;
	
	for (i = 0; i < 10; i ++)
	{
		rv = select(pipe_ids[0], &rfds, NULL, NULL, &tv);
		if (rv < 0)
		{
			perror ("Error during select");
			return EXIT_FAILURE;
		}
		rv = read (pipe_ids[0], &dat2, sizeof (dat2));
		if (rv == sizeof (dat2))
		{
			printf ("Got data: %c -> %d.\n", dat2.symb, dat2.val);
		}
	}
	close (pipe_ids[0]);
	printf ("Parent process: now exiting.\n");
	return EXIT_SUCCESS;
}
