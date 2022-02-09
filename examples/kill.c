#include <signal.h>
#include <unistd.h>

int	main()
{
	while(1)
	{
		kill(45434, SIGINT);
		sleep(10);
	}
	return (0);
}
