/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 01:41:43 by aoudija           #+#    #+#             */
/*   Updated: 2023/04/08 02:16:46 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(long time, char c, int pos, t_data *data)
{
	if (!data->write[0])
		return ;
	if (c == 'f')
		printf("\x1B[32m %ld Philosopher %d has taken a fork\033[0m\n", time, pos);
	else if (c == 'e')
		printf("\x1B[32m %ld Philosopher %d is eating\033[0m\n", time, pos);
	else if (c == 's')
		printf("\x1B[34m %ld Philosopher %d is sleeping\033[0m\n", time, pos);
	else if (c == 't')
		printf("\x1B[37m %ld Philosopher %d is thinking\033[0m\n", time, pos);
	else if (c == 'd')
		printf("\x1B[31m %ld Philosopher %d died\033[0m\n", time, pos);
}
