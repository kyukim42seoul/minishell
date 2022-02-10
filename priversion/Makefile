# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/04 15:55:45 by kyukim            #+#    #+#              #
#    Updated: 2022/02/10 20:35:31 by kyukim           ###   ########.fr        #
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
	split.o \


all : $(NAME) clean #.o 파일 보기 싫어서 임시조치

$(NAME) : $(OBJECTS)
	$(CC) -o $(NAME) $(CFLAGS) $(LIBRARYS) $(OBJECTS)

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
