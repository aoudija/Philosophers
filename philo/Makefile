# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 11:10:58 by aoudija           #+#    #+#              #
#    Updated: 2023/04/07 01:49:51 by aoudija          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

DEPS = philo.h

FILES = philo.c philo_utils.c routines.c check.c ft_print.c

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
