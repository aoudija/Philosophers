/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:00:20 by aoudija           #+#    #+#             */
/*   Updated: 2023/03/10 08:43:16 by aoudija          ###   ########.fr       */
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

int ft_atoi(const char *str);
typedef struct s_data
{
	pthread_mutex_t	mutex;
	int				nph;
	int				*fork;
	int				*table;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				*has_eaten;
	int				*is_alive;
	int				*has_slept;
	int				*has_thought;
}	t_data;


#endif