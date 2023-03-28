/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:55:36 by aoudija           #+#    #+#             */
/*   Updated: 2023/03/28 22:12:22 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

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

	while (all_ate(data))
	{
		i = -1;
		while (++i < data.nph)
		{
			if (get_time_ms() - data.t_ate[i] >= data.t_die)
			{
				time = get_time_ms() - data.t0;
				printf("\x1B[31m %ld Philosopher %d died\033[0m\n", time, i + 1);
				return ;
			}
		}
	}
}

void	amin(t_data data, char **av, int ac)
{
	if (ac == 6)
	{
		data.times_e = ft_atoi(av[5]);
		memset(data.ate, 0, data.nph * sizeof(int));
		// philo_n(data);
	}
	else if (ac == 5)
	{
		data.times_e = 1;
		memset(data.ate, -1, data.nph * sizeof(int));
		// philo_n(data);
	}
}

int main(int ac, char **av)
{
	t_data  data;
	int		i;
	char	**name;
	long	time;

	if (ac != 5 && ac != 6)
		return (0);
	data.fork = malloc(sizeof(sem_t *) * data.nph);
	data.ate = malloc(sizeof(int) * data.nph);
	data.t_ate = malloc(sizeof(long) * data.nph);
	data.nph = ft_atoi(av[1]);
	data.pid = malloc(sizeof(int) * data.nph);
    data.t_die = ft_atoi(av[2]);
    data.t_eat = ft_atoi(av[3]);
    data.t_sleep = ft_atoi(av[4]);
	name = malloc(sizeof(char *) * data.nph);
	i = -1;
	while (++i < data.nph)
		name[i] = ft_strjoin("/mysem_", ft_itoa(i));
	i = -1;
	while (++i < data.nph)
		data.fork[i] = sem_open(name[i], O_CREAT | O_EXCL, 0666, 1);
	amin(data, av, ac);
	data.t0 = get_time_ms();
	// i = -1;
	// while (++i < data.nph)
	// 	data.pid[i] = fork();
	// while (all_ate(data))
	// {
		i = -1;
		while (++i < data.nph)
		{
			data.pid[i] = fork();
			if (!data.pid[i] && i != data.nph)
			{
				if (i != data.nph - 1)
				{
					sem_wait(data.fork[i]);
					time = get_time_ms() - data.t0;
					printf("\x1B[32m %ld Philosopher %d has taken a fork\033[0m\n", time, i + 1);
					sem_wait(data.fork[i + 1]);
					data.t_ate[i] = get_time_ms();
					if (data.ate[i] == -1)
						;
					else
						data.ate[i] += 1;
					time = get_time_ms() - data.t0;
					printf("\x1B[32m %ld Philosopher %d has taken a fork\033[0m\n", time, i + 1);
					printf("\x1B[32m %ld Philosopher %d is eating\033[0m\n", time, i + 1);
					uusleepp(data.t_eat);
					break ;
				}
				else if (i == data.nph - 1)
				{
					sem_wait(data.fork[i]);
					time = get_time_ms() - data.t0;
					printf("\x1B[32m %ld Philosopher %d has taken a fork\033[0m\n", time, i + 1);
					sem_wait(data.fork[0]);
					data.t_ate[i] = get_time_ms();
					if (data.ate[i] == -1)
						;
					else
						data.ate[i] += 1;
					time = get_time_ms() - data.t0;
					printf("\x1B[32m %ld Philosopher %d has taken a fork\033[0m\n", time, i + 1);
					printf("\x1B[32m %ld Philosopher %d is eating\033[0m\n", time, i + 1);
					uusleepp(data.t_eat);
					break ;
				}
			}
	}
		if (i != data.nph - 1)
		{
			sem_post(data.fork[i]);
			sem_post(data.fork[i + 1]);
		}
		else if (i == data.nph - 1)
		{
			sem_post(data.fork[i]);
			sem_post(data.fork[0]);
		}
	// 	if (!data.pid[i] && i != data.nph)
	// 		break ;
	// }
	i = -1;
	while (++i < data.nph)
	{
		sem_close(data.fork[i]);
		sem_unlink(name[i]);
	}
	i = -1;
	while (++i < data.nph)
		waitpid(data.pid[i], NULL, 0);
}
