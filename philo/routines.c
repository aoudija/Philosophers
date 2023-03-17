/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:15:44 by aoudija           #+#    #+#             */
/*   Updated: 2023/03/17 20:18:24 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	normy1(t_data *data, int pos, long t0)
{
	if (pos != data->nph)
	{
		pthread_mutex_lock(&data->fork[pos - 1]);
		pthread_mutex_lock(&data->fork[pos]);
		data->t_ate[pos - 1] = get_time_ms();
		if (data->ate[pos - 1] == -1)
			;
		else
			data->ate[pos - 1] += 1;
		printf("\x1B[32m %ld Philosopher %d has taken a fork\033[0m\n", get_time_ms() - t0, pos);
		printf("\x1B[32m %ld Philosopher %d is eating\033[0m\n", get_time_ms() - t0, pos);
		uusleepp(data->t_eat);
		pthread_mutex_unlock(&data->fork[pos]);
		pthread_mutex_unlock(&data->fork[pos - 1]);
	}
}

void	normy2(t_data *data, int pos, long t0)
{
	if (pos == data->nph)
	{
		pthread_mutex_lock(&data->fork[pos - 1]);
		pthread_mutex_lock(&data->fork[0]);
		data->t_ate[pos - 1] = get_time_ms();
		if (data->ate[pos - 1] == -1)
			;
		else
			data->ate[pos - 1] += 1;
		printf("\x1B[32m %ld Philosopher %d has taken a fork\033[0m\n", get_time_ms() - t0, pos);
		printf("\x1B[32m %ld Philosopher %d is eating\033[0m\n", get_time_ms() - t0, pos);
		uusleepp(data->t_eat);
		pthread_mutex_unlock(&data->fork[0]);
		pthread_mutex_unlock(&data->fork[pos - 1]);
	}
}

void	*routine(void *sdata)
{
	t_data			*data;
	static long 	t0;
	static int		i;
	int				pos;

	data = (t_data *)sdata;
	if (i == 0)
		t0 = get_time_ms();
	i++;
	pos = i;
	data->t_ate[pos - 1] = t0;
	while (data->ate[pos - 1] < data->times_e)
	{
		//eat
		normy1(data, pos, t0);
		normy2(data, pos, t0);
		// sleep
		printf("\x1B[34m %ld Philosopher %d is sleeping\033[0m\n", get_time_ms() - t0, pos);
		uusleepp(data->t_sleep);
		//think
		printf("\x1B[37m %ld Philosopher %d is thinking\033[0m\n", get_time_ms() - t0, pos);
	}
	return (NULL);
}

