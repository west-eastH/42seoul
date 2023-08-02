ifdef WITH_BONUS
	NAME = checker
	INCLUDES	= ./checker_bonus.h
else
	NAME = push_swap
	INCLUDES	= ./push_swap.h
endif
NAME_BUNUS = checker

CC			= cc
CFLAG		= -Wall -Wextra -Werror

RM			= rm -f

MANDATORY	= ./ft_printf/ft_printf.c ./ft_printf/ft_format.c ./ft_printf/ft_putnbr.c ./libft/ft_split.c ./libft/libft.c ./init.c ./manage_stack.c ./push_b_to_a.c ./push_swap_utils.c ./push_swap.c ./set_num.c ./stack_push_pop.c ./ft_free.c

BONUS		= ./ft_printf/ft_printf_bonus.c ./ft_printf/ft_format_bonus.c ./ft_printf/ft_putnbr_bonus.c ./libft/ft_split_bonus.c ./libft/libft_bonus.c ./init_bonus.c ./manage_stack_bonus.c ./stack_push_pop_bonus.c ./get_next_line/get_next_line_bonus.c ./get_next_line/get_next_line_utils_bonus.c ./checker_bonus.c ./checker_utils_bonus.c ./ft_free.c

SRCS			= $(MANDATORY)
SRCS_BONUS		= $(BONUS)

ifdef WITH_BONUS
	OBJS = $(SRCS_BONUS:.c=.o)
else
	OBJS = $(SRCS:.c=.o)
endif

all : $(NAME)

bonus : 
	make WITH_BONUS=1 all

$(NAME) : $(OBJS)
		$(CC) $(CFLAG) $(OBJS) -o $(NAME)

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAG) -c $< -o $@

clean :
	$(RM) $(SRCS_BONUS:.c=.o) $(SRCS:.c=.o)

fclean : clean
	$(RM) $(NAME) $(NAME_BUNUS)

re : fclean all

.PHONY : all clean fclean re