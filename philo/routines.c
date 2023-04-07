/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:15:44 by aoudija           #+#    #+#             */
/*   Updated: 2023/04/07 03:51:54 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	normy1(t_data *data, int pos, long t0)
{
	long	time;

	if (pos != data->nph)
	{
		pthread_mutex_lock(&data->fork[pos - 1]);
		time = get_time_ms() - t0;
		ft_print(time, 'f', pos, data);
		pthread_mutex_lock(&data->fork[pos]);
		data->t_ate[pos - 1] = get_time_ms();
		if (data->ate[pos - 1] == -1)
			;
		else
			data->ate[pos - 1] += 1;
		time = get_time_ms() - t0;
		ft_print(time, 'f', pos, data);
		ft_print(time, 'e', pos, data);
		uusleepp(data->t_eat);
		pthread_mutex_unlock(&data->fork[pos]);
		pthread_mutex_unlock(&data->fork[pos - 1]);
	}
}

void	normy2(t_data *data, int pos, long t0)
{
	long	time;

	if (pos == data->nph)
	{
		pthread_mutex_lock(&data->fork[pos - 1]);
		time = get_time_ms() - t0;
		ft_print(time, 'f', pos, data);
		pthread_mutex_lock(&data->fork[0]);
		data->t_ate[pos - 1] = get_time_ms();
		if (data->ate[pos - 1] == -1)
			;
		else
			data->ate[pos - 1] += 1;
		time = get_time_ms() - t0;
		ft_print(time, 'f', pos, data);
		ft_print(time, 'e', pos, data);
		uusleepp(data->t_eat);
		pthread_mutex_unlock(&data->fork[0]);
		pthread_mutex_unlock(&data->fork[pos - 1]);
	}
}

void	*routine(void *sdata)
{
	t_data			*data;
	static long		t0;
	static int		i;
	int				pos;
	long			time;

	data = (t_data *)sdata;
	if (i == 0)
		t0 = get_time_ms();
	pthread_mutex_lock(data->mutex);
	i++;
	pos = i;
	data->t_ate[i] = get_time_ms();
	data->t_ate[pos - 1] = t0;
	pthread_mutex_unlock(data->mutex);
	while (data->ate[pos - 1] < data->times_e)
	{
		normy1(data, pos, t0);
		normy2(data, pos, t0);
		time = get_time_ms() - t0;
		ft_print(time, 's', pos, data);
		uusleepp(data->t_sleep);
		time = get_time_ms() - t0;
		ft_print(time, 't', pos, data);
	}
	return (NULL);
}
