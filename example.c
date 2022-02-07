#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int	main()
{
	int	rc;
	struct termios t;
	rc = tcgetattr(0, &t);
	printf("[%d] FLAG=[%lu]\n", rc, t.c_iflag);
	return (0);
}
