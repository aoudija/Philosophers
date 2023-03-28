/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:39:12 by aoudija           #+#    #+#             */
/*   Updated: 2023/03/27 01:00:42 by aoudija          ###   ########.fr       */
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

int		ft_atoi(const char *str);
typedef struct s_data
{
	sem_t	**fork;
	int		*pid;
	int		nph;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	long	*t_ate;
	long	t0;
	int		*ate;
	int		times_e;
}	t_data;
void	ph_b(t_data data, int i);
int		all_ate(t_data data);
int		ft_isdigit(int c);
int		good_to_go(char **s, int ac);
long	get_time_ms(void);
void	uusleepp(int time);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);

#endif