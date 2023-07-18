NAME = so_long

ifdef WITH_BONUS
	INCLUDES	= ./so_long_bonus.h
else
	INCLUDES	= ./so_long.h
endif
CC			= cc
CFLAG		= -Wall -Wextra -Werror

RM			= rm -f

MANDATORY	= main.c ft_printf/ft_format.c ft_printf/ft_printf.c ft_printf/ft_putnbr.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c libft.c init.c manage_stack.c map_utils.c map.c move.c map_utils2.c
BONUS		= main_bonus.c ft_printf/ft_format.c ft_printf/ft_printf.c ft_printf/ft_putnbr.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c libft_bonus.c init_bonus.c manage_stack_bonus.c map_utils_bonus.c map_bonus.c move_bonus.c map_utils2_bonus.c so_long_utils_bonus.c

SRCS		= $(MANDATORY)
SRCS_BONUS	= $(BONUS)

ifdef WITH_BONUS
	OBJS = $(SRCS_BONUS:.c=.o)
else
	OBJS = $(SRCS:.c=.o)
endif

all : $(NAME)

bonus : 
	make WITH_BONUS=1 all

$(NAME) : $(OBJS)
		$(CC) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAG) -Imlx -c $< -o $@

clean :
	$(RM) $(SRCS_BONUS:.c=.o) $(SRCS:.c=.o)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re