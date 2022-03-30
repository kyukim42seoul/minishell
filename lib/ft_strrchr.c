/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:01:54 by kbaek             #+#    #+#             */
/*   Updated: 2021/05/23 21:05:02 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	ch;
	int		i;

	str = (char *)s;
	ch = (char)c;
	i = 1;
	while (*str)
	{
		str++;
		i++;
	}
	while (i--)
	{
		if (*str == ch)
			return (str);
		str--;
	}
	return (NULL);
}
