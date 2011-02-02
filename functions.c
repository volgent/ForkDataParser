#include <unistd.h>
#include <stdlib.h>

#define STEPS 10

struct Data 
{
	char symb;
	int val;
};

int getMessage(int write_fd)
{
	struct Data dat1;
	int i;
	
	for (i = 0; i < 10; i++)
	{
		dat1.symb = i + 39;
		dat1.val = i;
		write (write_fd, &dat1, sizeof (dat1));
		sleep (1);
	}
	close(write_fd);
	return EXIT_SUCCESS;
}