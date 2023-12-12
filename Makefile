# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 16:28:21 by kyukim            #+#    #+#              #
#    Updated: 2022/03/30 11:23:11 by kyukim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
#CFLAGS = -Wall -Wextra -Werror
#LDFLAGS = -L/${HOME}/.brew/opt/readline/lib
#CPPFLAGS = -I/${HOME}/.brew/opt/readline/include
LIBRARYS = -lreadline
 LDFLAGS = -L/usr/local/opt/readline/lib
 CPPFLAGS = -I/usr/local/opt/readline/include

LIB_NAME	= libft.a
LIB_DIR		= ./lib

OBJECTS = ./srcs/proto.o \
		./srcs/signal.o \
		./srcs/init.o \
		./srcs/copy.o \
		./srcs/util.o \
		./srcs/add_str.o \
		./srcs/lst.o \
		./srcs/sh_lst.o \
		./srcs/free.o \
		./srcs/error.o \
		./srcs/tokenize/tokenize.o \
		./srcs/tokenize/tokenize_cmd_env.o \
		./srcs/tokenize/tokenize_util.o \
		./srcs/syntax/syntax_hub.o \
		./srcs/syntax/check_order.o \
		./srcs/set_type.o \
		./srcs/astree/parse.o \
		./srcs/astree/tree_util.o \
		./srcs/astree/tree_io.o \
		./srcs/astree/tree_bin.o \
		./srcs/astree/tree_arg.o \
		./srcs/astree/tree_pipe.o \
		./srcs/astree/del_tree.o \
		./srcs/builtin/builtin.o \
		./srcs/builtin/builtin_env.o \
		./srcs/builtin/builtin_unset.o \
		./srcs/builtin/builtin_export.o \
		./srcs/builtin/builtin_pwd.o \
		./srcs/builtin/builtin_cd.o \
		./srcs/builtin/builtin_echo.o \
		./srcs/builtin/builtin_exit.o \
		./srcs/cmd/redir.o \
		./srcs/cmd/redir_util.o \
		./srcs/cmd/heredoc.o \
		./srcs/cmd/execve.o \
		./srcs/cmd/exec_path.o \
		./srcs/action/action.o \
		./srcs/action/preorder.o \


all : $(NAME) clean

$(NAME) : $(OBJECTS)
	@make -C $(LIB_DIR)
	$(CC) -o $(NAME) $(CFLAGS) $(LIBRARYS) $(OBJECTS) $(CPPFLAGS) $(LDFLAGS) $(LIB_DIR)/$(LIB_NAME)

clean :
	@make -C $(LIB_DIR) clean
	rm -f $(OBJECTS)

fclean : clean
	@make -C $(LIB_DIR) fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
