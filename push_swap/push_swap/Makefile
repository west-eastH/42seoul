NAME		= libpush_swap.a

CC			= cc
CFLAG		= -Wall -Wextra -Werror

RM			= rm -f

AR			= ar
ARFLAGS		= rsc

INCLUDES	= ./push_swap.h

SRC			= ./ft_printf/ft_printf.c ./ft_printf/ft_format.c ./ft_printf/ft_putnbr.c ./libft/ft_split.c ./libft/libft.c ./init.c ./manage_stack.c ./push_b_to_a.c ./push_swap_utils.c ./push_swap.c ./set_num.c ./stack_push_pop.c
SRCS		= $(SRC)
OBJS =		$(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAG) -c $< -o $@

clean :
	$(RM) $(SRCS:.c=.o)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re