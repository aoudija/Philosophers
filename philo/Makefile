# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 11:10:58 by aoudija           #+#    #+#              #
#    Updated: 2023/03/13 15:05:54 by aoudija          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# B_NAME = 

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

DEPS = philo.h

FILES = philo.c philo_utils.c

# FILES_B = 

OBG = $(FILES:.c=.o)

# OBGB = $(FILES_B:.c=.o)

%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBG)
	$(CC) $(CFLAGS) $(OBG) -o $(NAME) 

# bonus : $(B_NAME)

# $(B_NAME) : $(OBGB)
# 	$(CC) $(CFLAGS) $(OBGB) -o $(B_NAME)

clean:
	rm -f $(OBG)
#  $(OBGB)

fclean: clean
	rm -f $(NAME)
#  $(B_NAME)
re:fclean all

.PHONY:all clean fclean re
#  bonus