NAME = pipex

CC			= cc
CFLAG		= -Wall -Wextra -Werror

RM			= rm -f

LIBS 		= ./libft/libft.a
SRCS		= main.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAG) $(OBJS) $(LIBS) -o $(NAME)

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAG) -c $< -o $@

clean :
	$(RM) $(SRCS:.c=.o)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re