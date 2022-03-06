#include "proto.h"

size_t	sh_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

char	*sh_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	char	*temp;

	s2 = (char *)malloc(sizeof(char) * (len + 1));
	temp = s2;
	if (!s)
		return (NULL);
	if (!s2)
		return (NULL);
	if (start >= sh_strlen(s))
	{
		*temp = '\0';
		return (s2);
	}
	while (len-- != 0 && *s)
		*temp++ = *(s + start++);
	*temp = '\0';
	return (s2);
}

char	*sh_strchr(const char *s, int c)
{
	char	cc;

	cc = (char)c;
	while (*s)
	{
		if (*s == cc)
			return ((char *)s);
		s++;
	}
	if (cc == '\0' && *s == '\0')
		return ((char *)s);
	return (NULL);
}

void	check_data(char *message, char **data)
{
	int	index;

	index = 0;
	if (data == NULL)
		return ;
	while (data[index])
	{
		printf("%s : ", message);
		printf("%s\n", data[index]);
		index++;
	}
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
	while (str[index])
		index++;
	size = index;
	new_buf = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_buf)
		printf("failed allocate add_str\n");
	index = 0;
	while (index < size)
	{
		new_buf[index] = ft_strdup(str[index]);
		index++;
	}
	new_buf[index] = ft_strdup(new[0]);
	new_buf[index + 1] = NULL;
	index = 0;
	while (str[index])
	{
		free(str[index]);
		index++;
	}
	free (str);
	free (new[0]);
	free (new);
	return (new_buf);
}