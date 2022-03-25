
NAME = minishell
#CC = gcc
CC = gcc# -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L/${HOME}/.brew/opt/readline/lib
CPPFLAGS = -I/${HOME}/.brew/opt/readline/include
LIBRARYS = -lreadline
# LDFLAGS = -L/usr/local/opt/readline/lib
# CPPFLAGS = -I/usr/local/opt/readline/include
#  LIBRARYS = -lreadline

LIB_NAME	= libft.a
# SRCS_DIR	= ./srcs/
LIB_DIR		= ./lib/

OBJECTS = ./srcs/proto.o \
		./srcs/signal.o \
		./srcs/init.o \
		./srcs/copy.o \
		./srcs/util.o \
		./srcs/add_str.o \
		./srcs/lst.o \
		./srcs/sh_lst.o \
		./srcs/free.o \
		./srcs/tokenize/tokenize.o \
		./srcs/tokenize/tokenize_cmd_env.o \
		./srcs/tokenize/tokenize_util.o \
		./srcs/free_token.o \
		./srcs/print_node.o \
		./srcs/syntax/syntax_hub.o \
		./srcs/syntax/check_order.o \
		./srcs/set_type.o \
		./srcs/astree/parse.o \
		./srcs/astree/tree_util.o \
		./srcs/builtin/builtin.o \
		./srcs/builtin/builtin_env.o \
		./srcs/builtin/builtin_unset.o \
		./srcs/builtin/builtin_export.o \
		./srcs/builtin/builtin_pwd.o \
		./srcs/builtin/builtin_cd.o \
		./srcs/builtin/builtin_echo.o \
		./srcs/builtin/builtin_exit.o \
		./srcs/cmd/redir.o \
		./srcs/cmd/heredoc.o \
		./srcs/cmd/execve.o \
		./srcs/action/action.o \
		./srcs/action/preorder.o \



# ALLSRCS	= $(addprefix $(SRCS_DIR), $(OBJECTS))

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
