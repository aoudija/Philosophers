/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:00:09 by aoudija           #+#    #+#             */
/*   Updated: 2023/03/17 20:11:41 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	norm1(t_data data)
{
	int	i;

	i = 0;
	while (data.ate[i] < data.times_e)
	{
		if ((get_time_ms() - data.t_ate[i]) >= data.t_die)
		{
			printf("\x1B[31m %ld Philosopher %d died\033[0m\n", get_time_ms() - data.t0, i + 1);
			return ;
		}
		if ((i  + 1) == data.nph)
			i = 0;
	}
}

void	philo_n(t_data data)
{
	pthread_t		*th;
	int				i;

	th = malloc(data.nph * sizeof(pthread_t));
	i = -1;
	while(++i < data.nph)
		pthread_mutex_init(&data.fork[i], NULL);
	i = -1;
	while (++i < data.nph)
		pthread_create(&th[i], NULL, routine, (void *)&data);
	data.t0 = get_time_ms();
	i = -1;
	while (++i < data.nph)
		pthread_join(th[i], NULL);
	i = -1;
	while(++i < data.nph)
		pthread_mutex_destroy(&data.fork[i]);
}

int	main(int ac, char **av)
{
	t_data	data;

	data.ac = ac;
	data.nph = ft_atoi(av[1]);
	data.fork = malloc(sizeof(pthread_mutex_t) * data.nph);
	data.t_ate = malloc(sizeof(long) * data.nph);
	data.ate = malloc(sizeof(int) * data.nph);
	data.t_die = ft_atoi(av[2]);
	data.t_eat = ft_atoi(av[3]);
	data.t_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data.times_e = ft_atoi(av[5]);
		memset(data.ate, 0, data.nph * sizeof(int));
		philo_n(data);
	}
	else
	{
		data.times_e = 1;
		memset(data.ate, -1, data.nph * sizeof(int));
		philo_n(data);
	}
	return (0);
}
