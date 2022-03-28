/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:10:30 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/25 20:14:21 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

t_token	*find_heredoc(t_token *token, int *child_number)
{
	t_token		*cur;
	static int	order;

	cur = token;
	while (cur->next)
	{
		if (cur->type == PIPE)
		{
			order++;
			(*child_number) = order;
		}
		if (cur->type == LEFT_DOUBLE_REDI)
			return (cur);
		cur = cur->next;
	}
	order = 0;
	return (token);
}
