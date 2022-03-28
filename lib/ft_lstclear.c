/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:24:00 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/28 16:48:39 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_lst_k **lst, void (*del)(void*))
{
	t_lst_k	*p_lst;

	if (!lst)
		return ;
	while (*lst)
	{
		p_lst = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = p_lst;
	}
}
