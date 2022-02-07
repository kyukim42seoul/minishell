#include <unistd.h>
#include <stdio.h>

int	main()
{
	printf("name : %s\n", ttyname(0));
	return (0);
}
