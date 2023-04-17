/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:55:36 by aoudija           #+#    #+#             */
/*   Updated: 2023/04/17 20:13:43 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	amin(t_data *data, char **av, int ac)
{
	if (ac == 6)
	{
		data->times_e = ft_atoi(av[5]);
		data->ate = 0;
	}
	else if (ac == 5)
	{
		data->times_e = 1;
		data->ate = -1;
	}
}

void	eat(t_data *data)
{
	long	time;

	sem_wait(data->fork);
	time = get_time_ms() - data->t0;
	ft_print(time, 'f', data->i + 1, data);
	sem_wait(data->fork);
	sem_wait(data->sem_t_ate);
	data->t_ate = get_time_ms();
	sem_post(data->sem_t_ate);
	sem_wait(data->sem_ate);
	if (data->ate == -1)
		;
	else
		data->ate += 1;
	sem_post(data->sem_ate);
	time = get_time_ms() - data->t0;
	ft_print(time, 'f', data->i + 1, data);
	ft_print(time, 'e', data->i + 1, data);
	uusleepp(data->t_eat);
	sem_post(data->fork);
	sem_post(data->fork);
}

void	*routine(void *sdata)
{
	t_data	*data;
	long	time;
	int		temp;

	data = (t_data *)sdata;
	sem_wait(data->sem_ate);
	temp = data->ate;
	sem_post(data->sem_ate);
	while (temp < data->times_e)
	{
		eat(data);
		time = get_time_ms() - data->t0;
		ft_print(time, 's', data->i + 1, data);
		uusleepp(data->t_sleep);
		time = get_time_ms() - data->t0;
		ft_print(time, 't', data->i + 1, data);
		sem_wait(data->sem_ate);
		temp = data->ate;
		sem_post(data->sem_ate);
	}
	sem_close(data->sem_ate);
	sem_close(data->sem_t_ate);
	sem_unlink(ft_strjoin("/t_ate", ft_itoa(data->i)));
	sem_unlink(ft_strjoin("/ate", ft_itoa(data->i)));
	exit (0);
}

void	do_this(t_data data, int ac, char **av)
{
	int			i;
	pthread_t	th;

	i = -1;
	while (++i < data.nph)
	{
		data.pid[i] = fork();
		if (!data.pid[i])
		{
			set_child_sems(&data, i);
			amin(&data, av, ac);
			data.t0 = get_time_ms();
			data.i = i;
			data.t_ate = get_time_ms();
			pthread_create(&th, NULL, routine, (void *)&data);
			death(&data);
		}
	}
}

int	main(int ac, char **av)
{
	t_data		data;
	int			i;

	if (ac != 5 || ac != 6)
	{
		if (!good_to_go(av, ac))
			return (0);
		data.nph = ft_atoi(av[1]);
		data.pid = malloc(sizeof(int) * data.nph);
		data.t_die = ft_atoi(av[2]);
		data.t_eat = ft_atoi(av[3]);
		data.t_sleep = ft_atoi(av[4]);
		sem_unlink("/mysem");
		sem_unlink("/write");
		data.write = sem_open("/write", O_CREAT, 0666, 1);
		data.fork = sem_open("/mysem", O_CREAT, 0666, data.nph);
		do_this(data, ac, av);
		waitpid(-1, NULL, 0);
		i = -1;
		while (++i < data.nph)
			kill(data.pid[i], SIGTERM);
		free(data.pid);
		normy_main(&data);
	}
	return (0);
}
