#include "proto.h"

int	str_array_size(char **str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

void	free_str_array(char **str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		free(str[index]);
		index++;
	}
	free(str);
}

char	**add_str(char **str, char **new)
{
	int		index;
	int		size;
	char	**new_buf;

	index = 0;
	size = 0;
	new_buf = 0;
	if (str == NULL)
		return (NULL);
	size = str_array_size(str);
	new_buf = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_buf)
		printf("add_str : %s\n", strerror(errno));
	while (index < size)
	{
		new_buf[index] = ft_strdup(str[index]);
		index++;
	}
	new_buf[index] = ft_strdup(new[0]);
	new_buf[index + 1] = NULL;
	free_str_array(str);
	free_str_array(new);
	return (new_buf);
}
