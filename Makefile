# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/04 15:55:45 by kyukim            #+#    #+#              #
#    Updated: 2022/02/06 18:40:38 by kyukim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBRARYS = -lreadline

OBJECTS = main.o \
	util.o \
	init.o \
	tokenize.o \
	lst.o \


all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) -o $(NAME) $(CFLAGS) $(LIBRARYS) $(OBJECTS)

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
