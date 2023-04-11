/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:00:20 by aoudija           #+#    #+#             */
/*   Updated: 2023/04/09 05:48:47 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>

long	ft_atoi(const char *str);
typedef struct s_data
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*mutexes;
	int				nph;
	long			*t_ate;
	long			t0;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				*ate;
	int				times_e;
}	t_data;
long	get_time_ms(void);
void	uusleepp(int time);
void	*routine(void *sdata);
int		all_ate(t_data data);
int		ft_isdigit(int c);
int		good_to_go(char **s, int ac);
void	ft_print(long time, char c, int pos, t_data *data);

#endif