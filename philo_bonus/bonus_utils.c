/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:17:19 by aoudija           #+#    #+#             */
/*   Updated: 2023/04/11 21:25:23 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

long	ft_atoi(const char *str)
{
	int		s;
	int		i;
	long	nb;

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
		usleep(100);
		gettimeofday(&tv, NULL);
		tt = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
}

void	death(t_data *data)
{
	long	time;

	while (1)
	{
		usleep(100);
		sem_wait(data->sem_t_ate);
		if (get_time_ms() - data->t_ate >= data->t_die)
		{
			sem_post(data->sem_t_ate);
			sem_wait(data->write);
			time = get_time_ms() - data->t0;
			printf("\x1B[31m %ld %d died\033[0m\n", time, data->i + 1);
			sem_close(data->sem_ate);
			sem_close(data->sem_t_ate);
			sem_unlink(ft_strjoin("/t_ate", ft_itoa(data->i)));
			sem_unlink(ft_strjoin("/ate", ft_itoa(data->i)));
			exit (0);
		}
		sem_post(data->sem_t_ate);
	}
}

void	set_child_sems(t_data *data, int i)
{
	char	*name;
	char	*name2;

	name = ft_strjoin("/t_ate", ft_itoa(i));
	name2 = ft_strjoin("/ate", ft_itoa(i));
	sem_unlink(name);
	sem_unlink(name2);
	data->sem_t_ate = sem_open(name, O_CREAT, 0666, 1);
	data->sem_ate = sem_open(name, O_CREAT, 0666, 1);
	free(name);
	free(name2);
}
