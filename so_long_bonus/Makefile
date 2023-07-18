
NAME = so_long
CC			= cc
CFLAG		= -Wall -Wextra -Werror

RM			= rm -f

SRCS			= main_bonus.c ft_printf/ft_format_bonus.c ft_printf/ft_printf_bonus.c ft_printf/ft_putnbr_bonus.c get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c libft_bonus.c init_bonus.c manage_stack_bonus.c map_utils_bonus.c map_bonus.c move_bonus.c map_utils2_bonus.c so_long_utils_bonus.c

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