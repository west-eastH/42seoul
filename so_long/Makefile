
NAME = so_long
CC			= cc
CFLAG		= -Wall -Wextra -Werror

RM			= rm -f

SRCS			= main.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)


$(NAME) : $(OBJS)
		$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -Imlx -c $< -o $@

clean :
	$(RM) $(SRCS:.c=.o)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re