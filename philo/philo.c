/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:00:09 by aoudija           #+#    #+#             */
/*   Updated: 2023/03/07 19:47:18 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *sdata)
{
	static int		pos;
	t_data			*data;
	int				i;
	static int		tt;
	struct timeval	start, end;

	data = (t_data *) sdata;
	pthread_mutex_lock(&data->mutex);
	pos++;
	i = 0;
	//eat
	gettimeofday(&start, NULL);
	if (data->fork[pos - 1] && data->fork[pos]
		&& !data->has_eaten[pos - 1] && data->is_alive[pos - 1])
	{
		printf("\x1B[32m %f Philosopher %d has taken a fork\033[0m\n", (float)start.tv_usec / 1000000, pos);
		printf("\x1B[32m %f Philosopher %d is eating\033[0m\n", (float)start.tv_usec / 1000000, pos);
		data->fork[pos] = 0;
		data->has_eaten[pos - 1] = 1;
		usleep(data->t_eat);
	}
	//sleep
	if(data->is_alive[pos - 1] && !data->has_slept[pos - 1])
	{
		printf("\x1B[34m %f Philosopher %d is sleeping\033[0m\n", (float)start.tv_usec / 1000000, pos);
		data->has_slept[pos - 1] = 1;
		usleep(data->t_sleep);
	}
	//think
	if(data->is_alive[pos - 1] && !data->has_thought[pos - 1])
	{
		printf("\x1B[37m %f Philosopher %d is thinking\033[0m\n", (float)start.tv_usec / 1000000, pos);
		data->has_thought[pos - 1] = 1;
	}
	gettimeofday(&end, NULL);
	tt += end.tv_usec - start.tv_usec;
	//die
	if (tt >= data->t_die && !data->has_eaten[pos - 1])
	{
		data->is_alive[pos - 1] = 0;
		printf("\x1B[31m %f Philosopher %d died\033[0m\n", (float)start.tv_usec / 1000000,pos);
	}
	pthread_mutex_unlock(&data->mutex);
	if (pos == data->nph)
		printf("-->%d\n", tt);
	// 	pos = 0;
	return (NULL);
}

int	*fill_tab_O(int nph)
{
	int	*tab;
	int	i;

	tab = malloc(sizeof(int) * nph);
	i = -1;
	while (++i < nph)
		tab[i] = 0;
	return (tab);
}

int	*fill_tab_1(int nph)
{
	int	*tab;
	int	i;

	tab = malloc(sizeof(int) * nph);
	i = -1;
	while (++i < nph)
		tab[i] = 1;
	return (tab);
}

int	main(int ac, char **av)
{
	pthread_t		*th;
	int				i;
	t_data			data;

	data.nph = ft_atoi(av[ac - 4]);
	data.fork = fill_tab_1(data.nph);
	data.has_eaten = fill_tab_O(data.nph);
	data.is_alive = fill_tab_1(data.nph);
	data.has_slept = fill_tab_O(data.nph);
	data.has_thought = fill_tab_O(data.nph);
	data.t_die = ft_atoi(av[ac - 3]);
	data.t_eat = ft_atoi(av[ac - 2]);
	data.t_sleep = ft_atoi(av[ac - 1]);
	th = malloc(data.nph * sizeof(pthread_t));
	pthread_mutex_init(&data.mutex, NULL);
	i = 0;
	while (++i <= data.nph)
		pthread_create(&th[i], NULL, routine, (void *)&data);
	i = 0;
	while (++i <= data.nph)
		pthread_join(th[i], NULL);
	pthread_mutex_destroy(&data.mutex);
	return (0);
}
