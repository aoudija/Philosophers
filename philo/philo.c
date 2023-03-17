/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:00:09 by aoudija           #+#    #+#             */
/*   Updated: 2023/03/17 08:36:23 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	// if (data->times_e != -1)
	while (1)
	{
		//eat
		if (pos != data->nph)
		{
			pthread_mutex_lock(&data->fork[pos - 1]);
			pthread_mutex_lock(&data->fork[pos]);
			data->t_ate[pos - 1] = get_time_ms();
			printf("\x1B[32m %ld Philosopher %d has taken a fork\033[0m\n", get_time_ms() - t0, pos);
			printf("\x1B[32m %ld Philosopher %d is eating\033[0m\n", get_time_ms() - t0, pos);
			uusleepp(data->t_eat);
			pthread_mutex_unlock(&data->fork[pos]);
			pthread_mutex_unlock(&data->fork[pos - 1]);
		}
		else if (pos == data->nph)
		{
			pthread_mutex_lock(&data->fork[pos - 1]);
			pthread_mutex_lock(&data->fork[0]);
			data->t_ate[pos - 1] = get_time_ms();
			printf("\x1B[32m %ld Philosopher %d has taken a fork\033[0m\n", get_time_ms() - t0, pos);
			printf("\x1B[32m %ld Philosopher %d is eating\033[0m\n", get_time_ms() - t0, pos);
			uusleepp(data->t_eat);
			pthread_mutex_unlock(&data->fork[0]);
			pthread_mutex_unlock(&data->fork[pos - 1]);
		}
		// sleep
		printf("\x1B[34m %ld Philosopher %d is sleeping\033[0m\n", get_time_ms() - t0, pos);
		uusleepp(data->t_sleep);
		//think
		printf("\x1B[37m %ld Philosopher %d is thinking\033[0m\n", get_time_ms() - t0, pos);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t		*th;
	int				i;
	t_data			data;

	data.ac = ac;
	data.nph = ft_atoi(av[1]);
	data.fork = malloc(sizeof(pthread_mutex_t) * data.nph);
	data.t_ate = malloc(sizeof(long) * data.nph);
	data.mutex = malloc(sizeof(pthread_mutex_t));
	data.is_alive = fill_tab(data.nph, 1);
	data.t_die = ft_atoi(av[2]);
	data.t_eat = ft_atoi(av[3]);
	data.t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data.times_e = ft_atoi(av[5]);
	else
		data.times_e = -1;
	th = malloc(data.nph * sizeof(pthread_t));
	pthread_mutex_init(data.mutex, NULL);
	i = -1;
	while(++i < data.nph)
		pthread_mutex_init(&data.fork[i], NULL);
	i = -1;
	while (++i < data.nph)
		pthread_create(&th[i], NULL, routine, (void *)&data);
	data.t0 = get_time_ms();
	i = 0;
	while (1)
	{
		if ((get_time_ms() - data.t_ate[i]) >= data.t_die)
		{
			printf("\x1B[31m %ld Philosopher %d died\033[0m\n", get_time_ms() - data.t0, i + 1);
			return (0);
		}
		if ((i  + 1) == data.nph)
			i = 0;
	}
	i = -1;
	while (++i < data.nph)
		pthread_join(th[i], NULL);
	i = -1;
	while(++i < data.nph)
		pthread_mutex_destroy(&data.fork[i]);
	pthread_mutex_destroy(data.mutex);
	return (0);
}
