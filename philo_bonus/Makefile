# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/18 12:00:16 by aoudija           #+#    #+#              #
#    Updated: 2023/04/07 20:05:26 by aoudija          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

DEPS = philo.h

FILES = philo_b.c bonus_utils.c check.c ft_print.c

OBG = $(FILES:.c=.o)

%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBG)
	$(CC) $(CFLAGS) $(OBG) -o $(NAME)

clean:
	rm -f $(OBG)

fclean: clean
	rm -f $(NAME)

re:fclean all

.PHONY:all clean fclean re
