/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:25:01 by kyukim            #+#    #+#             */
/*   Updated: 2022/02/04 19:09:41 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

t_list	*sh_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

t_list	*sh_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	sh_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == NULL)
		*lst = new;
	sh_lstlast(*lst)->next = new;
	new->next = NULL;
}

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

int	sh_strcmp(char *dst, char *src)
{
	int	index;
	int	dst_lenth;
	int	src_lenth;

	index = 0;
	dst_lenth = sh_strlen(dst);
	src_lenth = sh_strlen(src);
	if (dst_lenth != src_lenth)
		return (EXIT_FAILURE);
	while (dst_lenth--)
	{
		if (dst[index] == src[index])
			index++;
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
