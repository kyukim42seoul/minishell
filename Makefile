NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -L/${HOME}/.brew/opt/readline/lib

CPPFLAGS = -I/${HOME}/.brew/opt/readline/include

LIBRARYS = -lreadline

OBJECTS = proto.o \
	init.o \
	copy.o \
	util.o \
	lst.o \

all : $(NAME)

$(NAME) : $(OBJECTS)
	@$(CC) -o $(NAME) $(CFLAGS) $(LIBRARYS) $(OBJECTS) $(CPPFLAGS) $(LDFLAGS)

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
