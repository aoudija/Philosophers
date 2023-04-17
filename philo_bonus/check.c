/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:06:01 by aoudija           #+#    #+#             */
/*   Updated: 2023/04/17 20:12:05 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

int	ft_strlenn(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c <= 57 && c >= 48)
		return (1);
	return (0);
}

int	good_to_go(char **s, int ac)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (++j < ft_strlenn(s[i]))
		{
			if (!ft_isdigit(s[i][j]))
				return (0);
		}
	}
	return (1);
}

void	normy_main(t_data *data)
{
	sem_close(data->fork);
	sem_close(data->write);
	sem_unlink("/mysem");
	sem_unlink("/write");
}
