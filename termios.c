#include <stdio.h>
#include <sys/termios.h>

int	main()
{
	struct termios old;

	tcgetattr(0, &old);
	printf("%lu %lu %lu %lu\n", old.c_iflag, old.c_oflag, old.c_cflag ,old.c_lflag);
	return (0);
}
