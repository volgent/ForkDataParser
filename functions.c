#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

struct Data 
{
	char symb;
	int val;
};

int Write_fd;

void sigTermHandler(int id)
{
	printf ("Child process: Exiting now.\n");
	close (Write_fd);
	exit (EXIT_SUCCESS);
}

int getMessage(int write_fd)
{
	struct Data dat1;
	struct sigaction sa;
	int i;
	
	Write_fd = write_fd;
	sa.sa_handler = sigTermHandler;		/*Setting handler function*/
	sigaction (SIGTERM, &sa, 0);		/*Setting SIGTERM signal to hear*/
	
	for (i = 0; i < 10; i++)
	{
		dat1.symb = i + 39;
		dat1.val = i;
		write (write_fd, &dat1, sizeof (dat1));
		sync();
		sleep (1);
	}
	return EXIT_SUCCESS;
}