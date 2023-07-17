
NAME = so_long
CC			= cc
CFLAG		= -Wall -Wextra -Werror

RM			= rm -f

SRCS			= main.c ft_printf/ft_format.c ft_printf/ft_printf.c ft_printf/ft_putnbr.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c libft.c init.c manage_stack.c map_utils.c map.c move.c map_utils2.c

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