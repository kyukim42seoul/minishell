NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L/Users/kyukim/.brew/opt/readline/lib
CPPFLAGS = -I/Users/kyukim/.brew/opt/readline/include
LIBRARYS = -lreadline

OBJECTS = proto.o \

all : $(NAME) clean #.o 파일 보기 싫어서 임시조치

$(NAME) : $(OBJECTS)
	$(CC) -o $(NAME) $(CFLAGS) $(LIBRARYS) $(OBJECTS)

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
