/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 01:41:43 by aoudija           #+#    #+#             */
/*   Updated: 2023/04/07 20:10:24 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	ft_print(long time, char c, int pos, t_data *data)
{
	sem_wait(data->write);
	if (c == 'f')
		printf("\x1B[32m %ld Philosopher %d has taken a fork\033[0m\n", time, pos);
	else if (c == 'e')
		printf("\x1B[32m %ld Philosopher %d is eating\033[0m\n", time, pos);
	else if (c == 's')
		printf("\x1B[34m %ld Philosopher %d is sleeping\033[0m\n", time, pos);
	else if (c == 't')
		printf("\x1B[37m %ld Philosopher %d is thinking\033[0m\n", time, pos);
	sem_post(data->write);
}
