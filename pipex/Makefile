NAME = pipex

CC			= cc
CFLAG		= -Wall -Wextra -Werror

RM			= rm -f

LIBS 		= ./libft/libft.a
SRCS		= pipex_bonus.c pipex_utils_bonus.c manage_child_bonus.c get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c
INCLUDES	= pipex.h

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		@cd libft && $(MAKE)
		$(CC) $(CFLAG) $(OBJS) $(LIBS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

clean :
	$(RM) $(SRCS:.c=.o)
	@cd libft && $(MAKE) clean

fclean : clean
	$(RM) $(NAME) $(LIBS)

re : fclean all

.PHONY : all clean fclean