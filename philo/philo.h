/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:00:20 by aoudija           #+#    #+#             */
/*   Updated: 2023/03/20 09:18:25 by aoudija          ###   ########.fr       */
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

int		ft_atoi(const char *str);
typedef struct s_data
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*mutex;
	int				nph;
	long			*t_ate;
	long			t0;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				*ate;
	int				times_e;
}	t_data;
long	get_time_ms(void);
void	uusleepp(int time);
void	*routine(void *sdata);
int		all_ate(t_data data);
int		ft_isdigit(int c);
int		good_to_go(char **s, int ac);

#endif