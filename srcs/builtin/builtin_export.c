/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:20:27 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/29 14:24:43 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	export kk  			밸류가  null 이거나
	export kk=aa  		밸류가 있을 때.
	인자 i 를 통해서 두 경우 중 어떤 상황인지 체크.
*/
char	*find_value_status(char *str, int len, int status)
{
	char	*result;

	result = NULL;
	if (status == 1)
		result = ft_strdup("");
	else if (status == 2)
		result = ft_substr(str, len + 1, ft_strlen(str));
	else if (status == 3)
		result = NULL;
	return (result);
}

/*
	status 1 = 밸류가 빈문자열 ""  ex) export kk=""
	status 2 = 밸류가 있을 때. 		 ex) export kk=aa 
	starus 3 = 밸류가  null.     		 ex)  export kk  
*/
void	export_value(t_info *info, char *str, int len, int status)
{
	int		flag;
	char	*content;
	t_list	*cur;

	flag = 0;
	cur = info->e_head->next;
	content = find_value_status(str, len, status);
	while (cur)
	{
		if (!ft_strncmp(cur->key, str, len))
		{
			if (status != 3)
			{
				free(cur->content);
				cur->content = content;
			}
			flag = 1;
			break ;
		}
		cur = cur->next;
	}
	if (flag == 0)
		env_add(info, sh_substr(str, 0, len), content);
}

void	print_export(t_info *info, int fd)
{
	t_list	*check;

	check = info->e_head->next;
	while (check != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd((char *)check->key, fd);
		if (check->content != NULL)
		{
			ft_putchar_fd('=', fd);
			ft_putchar_fd('"', fd);
			ft_putstr_fd((char *)check->content, fd);
			ft_putchar_fd('"', fd);
		}
		ft_putchar_fd('\n', fd);
		check = check->next;
	}
}

int	before_value(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		i++;
		str++;
	}
	return (i);
}

/*
	[예시]
	export test 		-> export 에서 출력 o, env 에서 출력 x
	export test= 		-> export 에서 출력 o, env 에서 출력 o 대신 value = "" 인 상태
	export test1 test2	-> export 에서 출력 o test1, test2 총 두개가 올라감, env 에서 출력 x
	export test1= test2	-> export 에서 출력 o test1, test2 총 두개가 올라감,
							env 에서 test1 만 출력. 대신 value = "" 인 상태
*/
void	builtin_export(t_info *info, char **str)
{
	int		len;
	int		i;

	len = str_len(str);
	if (len == 1)
		print_export(info, 1);
	else
	{
		g_exit_signal = 0;
		while (*(++str))
		{
			i = before_value(*str);
			if (i == 0)
				error_one(str, 2);
			else if (i + 1 == (int)ft_strlen(*str) && (*str)[i] == '=')
				export_value(info, *str, i, 1);
			else if ((*str)[i] == '=')
				export_value(info, *str, i, 2);
			else
				export_value(info, *str, i, 3);
		}
	}
}
