/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:09:01 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/25 19:09:01 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	syntax_hub(t_token *head, t_debug *debug)
{
	t_token	*cur;

	cur = 0;
	if (head == NULL)
		return (EXIT_FAILURE);
	cur = head->next;
	while (cur->next)
	{
		if (check_order(cur, debug) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		cur = cur->next;
	}
	if (check_order(cur, debug) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
