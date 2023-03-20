# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 11:10:58 by aoudija           #+#    #+#              #
#    Updated: 2023/03/20 09:16:50 by aoudija          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

DEPS = philo.h

FILES = philo.c philo_utils.c routines.c check.c

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
