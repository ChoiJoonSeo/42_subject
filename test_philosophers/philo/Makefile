# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yeham <yeham@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 17:20:27 by yeham             #+#    #+#              #
#    Updated: 2023/02/28 13:47:47 by yeham            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c time.c operate1.c operate2.c ft_atoi.c etc.c

OBJS = $(SRCS:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)
$(NAME): $(OBJS) philo.h
	cc $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	cc $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean :
	make clean
	rm -f $(NAME)

re : 
	make fclean
	make all

.PHONY : all clean fclean re
