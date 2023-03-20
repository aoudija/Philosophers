/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:00:09 by aoudija           #+#    #+#             */
/*   Updated: 2023/03/20 09:18:20 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_ate(t_data data)
{
	int	i;

	i = 0;
	while (i < data.nph)
	{
		if (data.ate[i] < data.times_e)
			return (1);
		i++;
	}
	return (0);
}

void	norm1(t_data data)
{
	int		i;
	long	time;

	i = 0;
	while (all_ate(data))
	{
		while (i < data.nph)
		{
			if (get_time_ms() - data.t_ate[i] >= data.t_die)
			{
				time = get_time_ms() - data.t0;
				printf("\x1B[31m %ld Philosopher %d died\033[0m\n", time, i + 1);
				return ;
			}
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
	while (++i < data.nph)
		pthread_create(&th[i], NULL, routine, (void *)&data);
	data.t0 = get_time_ms();
	uusleepp(300);
	norm1(data);
	// usleep(500);
	i = -1;
	while (++i < data.nph)
		pthread_mutex_destroy(&data.fork[i]);
	free(th);
}

void	fill(t_data data, char **av)
{
	data.nph = ft_atoi(av[1]);
	data.fork = malloc(sizeof(pthread_mutex_t) * data.nph);
	data.mutex = malloc(sizeof(pthread_mutex_t));
	data.t_ate = malloc(sizeof(long) * data.nph);
	data.ate = malloc(sizeof(int) * data.nph);
	data.t_die = ft_atoi(av[2]);
	data.t_eat = ft_atoi(av[3]);
	data.t_sleep = ft_atoi(av[4]);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (!good_to_go(av, ac));
			return (0);
		fill (data, av);
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
		return (free(data.fork), free(data.ate)
			, free(data.t_ate), free(data.mutex), 0);
	}
	return (0);
}
