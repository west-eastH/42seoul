NAME		= libpush_swap.a

CC			= cc
CFLAG		= -Wall -Wextra -Werror

RM			= rm -f

AR			= ar
ARFLAGS		= rsc

INCLUDES	= ./push_swap.h

SRC			= ./ftprintf/ft_printf.c ./ftprintf/ft_format.c ./ftprintf/ft_putnbr.c ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c ./libft/ft_split.c ./libft/libft.c ./manage_stack.c ./push_b_to_a.c ./push_swap_utils.c ./push_swap.c ./set_num.c ./stack_push_pop.c
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