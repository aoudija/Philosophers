/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:39:12 by aoudija           #+#    #+#             */
/*   Updated: 2023/04/11 03:55:28 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_B_H
# define PHILO_B_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>

long	ft_atoi(const char *str);
typedef struct s_data
{
	sem_t	*fork;
	sem_t	*write;
	sem_t	*sem_t_ate;
	sem_t	*sem_ate;
	int		*pid;
	int		nph;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	long	t_ate;
	long	t0;
	int		ate;
	int		times_e;
	int		i;
}	t_data;
int		all_ate(t_data data);
int		ft_isdigit(int c);
int		good_to_go(char **s, int ac);
long	get_time_ms(void);
void	uusleepp(int time);
void	death(t_data *data);
void	ft_print(long time, char c, int pos, t_data *data);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	set_child_sems(t_data *data, int i);

#endif