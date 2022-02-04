# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/04 15:55:45 by kyukim            #+#    #+#              #
#    Updated: 2022/02/04 18:03:48 by kyukim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBRARYS = -lreadline

OBJECTS = main.o \
	util.o



all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) -o $(NAME) $(CFLAGS) $(LIBRARYS) $(OBJECTS)

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
