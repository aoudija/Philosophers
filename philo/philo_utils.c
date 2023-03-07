/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:17:19 by aoudija           #+#    #+#             */
/*   Updated: 2023/03/04 11:17:59 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	s;
	int	i;
	int	nb;

	s = 1;
	i = 0;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\r' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' )
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * s);
}
