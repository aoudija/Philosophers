/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:17:19 by aoudija           #+#    #+#             */
/*   Updated: 2023/03/18 11:46:35 by aoudija          ###   ########.fr       */
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

long	get_time_ms(void)
{
	long			i;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	i = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (i);
}

void	uusleepp(int time)
{
	struct timeval	tv;
	long			tt;
	long			diff;

	gettimeofday(&tv, NULL);
	tt = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	diff = tt + time;
	while (tt != diff)
	{
		usleep(1);
		gettimeofday(&tv, NULL);
		tt = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
}
