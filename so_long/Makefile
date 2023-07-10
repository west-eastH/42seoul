
NAME = so_long
CC			= cc
CFLAG		= -Wall -Wextra -Werror -lmlx -framework OpenGL -framework Appkit

RM			= rm -f

INCLUDES	= ./push_swap.h
SRCS			= ./main.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)


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