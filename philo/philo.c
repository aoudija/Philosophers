/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:00:09 by aoudija           #+#    #+#             */
/*   Updated: 2023/04/11 21:53:39 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_ate(t_data data)
{
	int	i;

	i = 0;
	while (i < data.nph)
	{
		pthread_mutex_lock(&data.mutexes[2]);
		if (data.ate[i] < data.times_e)
		{
			pthread_mutex_unlock(&data.mutexes[2]);
			return (1);
		}
		pthread_mutex_unlock(&data.mutexes[2]);
		i++;
	}
	return (0);
}

void	death(t_data data)
{
	int		i;
	long	time;

	i = 0;
	while (all_ate(data))
	{
		usleep(100);
		while (i < data.nph)
		{
			pthread_mutex_lock(&data.mutexes[1]);
			if (get_time_ms() - data.t_ate[i] >= data.t_die)
			{
				usleep(100);
				time = get_time_ms() - data.t0;
				ft_print(time, 'd', i + 1, &data);
				pthread_mutex_unlock(&data.mutexes[1]);
				return ;
			}
			pthread_mutex_unlock(&data.mutexes[1]);
			i++;
		}
		i = 0;
	}
}

void	philo_n(t_data data)
{
	pthread_t		*th;
	int				i;

	th = malloc(data.nph * sizeof(pthread_t));
	i = -1;
	while (++i < data.nph)
		pthread_mutex_init(&data.fork[i], NULL);
	i = -1;
	while (++i < 4)
		pthread_mutex_init(&data.mutexes[i], NULL);
	data.t0 = get_time_ms();
	i = -1;
	while (++i < data.nph)
	{
		usleep(100);
		pthread_create(&th[i], NULL, routine, (void *)&data);
	}
	death(data);
	i = -1;
	while (++i < data.nph)
		pthread_mutex_destroy(&data.fork[i]);
	i = -1;
	while (++i < 4)
		pthread_mutex_destroy(&data.mutexes[i]);
	free(th);
}

void	amin(t_data data, char **av, int ac)
{
	if (ac == 6)
	{
		data.times_e = ft_atoi(av[5]);
		memset(data.ate, 0, data.nph * sizeof(int));
		philo_n(data);
	}
	else if (ac == 5)
	{
		data.times_e = 1;
		memset(data.ate, -1, data.nph * sizeof(int));
		philo_n(data);
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (!good_to_go(av, ac))
			return (0);
		data.nph = ft_atoi(av[1]);
		data.fork = malloc(sizeof(pthread_mutex_t) * data.nph);
		data.mutexes = malloc(sizeof(pthread_mutex_t *) * 3);
		data.t_ate = malloc(sizeof(long) * data.nph);
		data.ate = malloc(sizeof(int) * data.nph);
		data.t_die = ft_atoi(av[2]);
		data.t_eat = ft_atoi(av[3]);
		data.t_sleep = ft_atoi(av[4]);
		amin(data, av, ac);
		return (free(data.fork), free(data.ate)
			, free(data.t_ate), free(data.mutexes), 0);
	}
	return (0);
}
