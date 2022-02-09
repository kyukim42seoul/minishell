#include <stdio.h>
#include <unistd.h>
#include <term.h>
#include <curses.h>

int	main()
{
	char	*buf;
	char	*name;
	int		result;

	name = ttyname(0);
	printf("pre_name : %s\n", name);
	result = tgetent(buf, "ttys002");
	printf("terminal : %d %s\n", result, buf);
	return (0);
}
