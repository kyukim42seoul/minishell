/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:20:39 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/28 21:40:16 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valid_key(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void	rm_env(t_info *info, char *str)
{
	t_list	*check;
	t_list	*temp;

	temp = NULL;
	check = info->e_head->next;
	while (check)
	{
		if (!ft_strncmp(str, check->key, ft_strlen(check->key)))
		{
			if (check == info->e_head)
				info->e_head = check->next;
			else
				temp->next = check->next;
			free(check->key);
			free(check->content);
			free(check);
			break ;
		}
		else
		{
			temp = check;
			check = check->next;
		}
	}
	g_exit_signal = 0;
}

void	builtin_unset(t_info *info, char **str)
{
	int		len;
	char	*error;

	error = NULL;
	len = str_len(str);
	if (len > 1)
	{
		while (*(++str))
		{
			if (valid_key(*str))
				rm_env(info, *str);
			else
			{
				error = ft_strjoin(ft_strjoin("bash: unset: ", *str),
						": not a valid identifier\n");
				write(2, error, ft_strlen(error));
				g_exit_signal = 1;
				free(error);
			}
		}
	}
}
