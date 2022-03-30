/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:43:21 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/28 16:48:32 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_lst_k **lst, t_lst_k *new)
{
	t_lst_k	*p_lst;

	if (!lst)
		return ;
	else if (!*lst)
		*lst = new;
	else
	{
		p_lst = *lst;
		while (p_lst->next)
			p_lst = p_lst->next;
		p_lst->next = new;
	}
}
