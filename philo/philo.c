/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:00:09 by aoudija           #+#    #+#             */
/*   Updated: 2023/03/10 10:17:31 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	didnt_eat_yet(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nph)
	{
		if (!data->has_eaten[i])
			return (0);
	}
	return (1);
}

long int	get_time_ms()
{
	long int		i;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	i = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (i);
}

int	*fill_table(t_data *data)
{
	int	i;

	
}

void	*routine(void *sdata)
{
	static int		pos;
	int				i;
	t_data			*data;
	static long int	tt;

	data = (t_data *) sdata;
	pthread_mutex_lock(&data->mutex);
	pos++;
	if (pos == 1)
		tt = get_time_ms();
	//die
	i = 0;
	if ((get_time_ms() - tt) >= data->t_die)
	{
		while (i < data->nph)
		{
			if (!data->has_eaten[i] && data->is_alive[i])
			{
				data->is_alive[i] = 0;
				printf("\x1B[31m %ld Philosopher %d died\033[0m\n", get_time_ms() - tt, i + 1);
			}
			i++;
		}
	}
	//eat
	if (data->fork[pos - 1] && data->fork[pos]
		&& !data->has_eaten[pos - 1] && data->is_alive[pos - 1])
	{
		printf("\x1B[32m %ld Philosopher %d has taken a fork\033[0m\n", get_time_ms() - tt, pos);
		printf("\x1B[32m %ld Philosopher %d is eating\033[0m\n", get_time_ms() - tt, pos);
		data->table[pos - 1] = data->fork[pos - 1];
		data->table[pos] = data->fork[pos];
		data->has_eaten[pos - 1] = 1;
		usleep(data->t_eat * 1000);
	}
	//sleep
	if(data->is_alive[pos - 1] && !data->has_slept[pos - 1])
	{
		printf("\x1B[34m %ld Philosopher %d is sleeping\033[0m\n", get_time_ms() - tt, pos);
		data->has_slept[pos - 1] = 1;
		usleep(data->t_sleep * 1000);
	}
	//think
	if(data->is_alive[pos - 1] && !data->has_thought[pos - 1])
	{
		printf("\x1B[37m %ld Philosopher %d is thinking\033[0m\n", get_time_ms() - tt, pos);
		data->has_thought[pos - 1] = 1;
	}
	pthread_mutex_unlock(&data->mutex);
	return (NULL);
}

void	*routine1(void *sdata)
{
	t_data			*data;
	static long int	tt;
	static int		pos;

	if (pos == 0)
		tt = get_time_ms();
	data = (t_data *) sdata;
	while (!didnt_eat_yet(data) && (get_time_ms() - tt) < data->t_die)
	{
		routine(sdata);
	}
	return (NULL);
}

int	*fill_tab(int nph, int n)
{
	int	*tab;
	int	i;

	tab = malloc(sizeof(int) * nph);
	i = -1;
	while (++i < nph)
		tab[i] = n;
	return (tab);
}

int	main(int ac, char **av)
{
	pthread_t		*th;
	int				i;
	t_data			data;

	data.nph = ft_atoi(av[ac - 4]);
	data.fork = fill_tab(data.nph, 1);
	data.table = fill_tab(data.nph * 2, 0);
	data.has_eaten = fill_tab(data.nph, 0);
	data.is_alive = fill_tab(data.nph, 1);
	data.has_slept = fill_tab(data.nph, 0);
	data.has_thought = fill_tab(data.nph, 0);
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
	i = -1;
	while (++i < data.nph)
	{
		printf("X -> %d for ->%d\n", i + 1, data.fork[i]);
	}
	return (0);
}
