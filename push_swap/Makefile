NAME		= libpush_swap.a

CC			= cc
CFLAG		= -Wall -Wextra -Werror

RM			= rm -f

AR			= ar
ARFLAGS		= rsc

INCLUDES	= ./push_swap.h

MANDATORY	= ./ft_printf/ft_printf.c ./ft_printf/ft_format.c ./ft_printf/ft_putnbr.c ./libft/ft_split.c ./libft/libft.c ./init.c ./manage_stack.c ./push_b_to_a.c ./push_swap_utils.c ./push_swap.c ./set_num.c ./stack_push_pop.c

BONUS		= ./get_next_line/get_next_line_bonus.c ./get_next_line/get_next_line_utils_bonus.c ./checker_bonus.c ./checker_utils_bonus.c

SRCS			= $(MANDATORY)
SRCS_BONUS		= $(BONUS) $(MANDATORY)

ifdef WITH_BONUS
	OBJS = $(SRCS_BONUS:.c=.o)
else
	OBJS = $(SRCS:.c=.o)
endif

all : $(NAME)

bonus : 
	make WITH_BONUS=1 all

$(NAME) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAG) -c $< -o $@

clean :
	$(RM) $(SRCS_BONUS:.c=.o) $(SRCS:.c=.o)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re