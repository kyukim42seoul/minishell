#include "../proto.h"

int	change_stdout(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("CHANGE_STDOUT\n");
		printf("%s\n", strerror(errno));
		return (-1);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	change_stdin(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("CHANGE_STDIN\n");
		printf("%s\n", strerror(errno));
		return (-1);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
