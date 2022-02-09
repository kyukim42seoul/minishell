#include <unistd.h>
#include <stdio.h>

int	main()
{
	printf("slot : %d\n", ttyslot());
	while (1)
		;
	return (0);
}
