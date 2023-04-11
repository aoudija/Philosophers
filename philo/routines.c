/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:15:44 by aoudija           #+#    #+#             */
/*   Updated: 2023/04/11 21:56:00 by aoudija          ###   ########.fr       */
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
		pthread_mutex_unlock(&data->mutexes[1]);
		data->t_ate[pos - 1] = get_time_ms();
		pthread_mutex_unlock(&data->mutexes[1]);
		pthread_mutex_lock(&data->mutexes[2]);
		if (data->ate[pos - 1] == -1)
			;
		else
			data->ate[pos - 1] += 1;
		pthread_mutex_unlock(&data->mutexes[2]);
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
		pthread_mutex_lock(&data->mutexes[1]);
		data->t_ate[pos - 1] = get_time_ms();
		pthread_mutex_unlock(&data->mutexes[1]);
		pthread_mutex_lock(&data->mutexes[2]);
		if (data->ate[pos - 1] == -1)
			;
		else
			data->ate[pos - 1] += 1;
		pthread_mutex_unlock(&data->mutexes[2]);
		time = get_time_ms() - t0;
		ft_print(time, 'f', pos, data);
		ft_print(time, 'e', pos, data);
		uusleepp(data->t_eat);
		pthread_mutex_unlock(&data->fork[0]);
		pthread_mutex_unlock(&data->fork[pos - 1]);
	}
}

void	normyyy(int pos, t_data *data)
{
	long	time;

	normy1(data, pos, data->t0);
	normy2(data, pos, data->t0);
	time = get_time_ms() - data->t0;
	ft_print(time, 's', pos, data);
	uusleepp(data->t_sleep);
	time = get_time_ms() - data->t0;
	ft_print(time, 't', pos, data);
}

void	*routine(void *sdata)
{
	t_data			*data;
	static int		i;
	int				pos;
	int				temp;

	data = (t_data *)sdata;
	pthread_mutex_lock(&data->mutexes[0]);
	i++;
	pos = i;
	pthread_mutex_unlock(&data->mutexes[0]);
	pthread_mutex_lock(&data->mutexes[1]);
	data->t_ate[pos - 1] = data->t0;
	pthread_mutex_unlock(&data->mutexes[1]);
	pthread_mutex_lock(&data->mutexes[2]);
	temp = data->ate[pos - 1];
	pthread_mutex_unlock(&data->mutexes[2]);
	while (temp < data->times_e)
	{
		normyyy(pos, data);
		pthread_mutex_lock(&data->mutexes[2]);
		temp = data->ate[pos - 1];
		pthread_mutex_unlock(&data->mutexes[2]);
	}
	return (NULL);
}
