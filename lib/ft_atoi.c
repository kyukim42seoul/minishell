/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 13:02:01 by kbaek             #+#    #+#             */
/*   Updated: 2022/01/03 14:50:24 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long long	mul;
	int			min;

	min = 1;
	mul = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			min *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		if (mul * min > 2147483647 || mul * min < -2147483648)
			return (-1);
		else
			mul = mul * 10 + (*str - '0');
		str++;
	}
	if (*str == '-' || *str == '+')
		return (-1);
	return (mul * min);
}
