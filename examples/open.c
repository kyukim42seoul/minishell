#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int fd;

	fd = open("temp.txt", O_RDONLY);
	while (1)
		;
	return (0);
}
