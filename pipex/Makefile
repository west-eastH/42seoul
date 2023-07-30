NAME = pipex
ifdef WITH_BONUS
	INCLUDES	= ./pipex_bonus.h
else
	INCLUDES	= ./pipex.h
endif
CC			= cc
CFLAG		= -Wall -Wextra -Werror

RM			= rm -f

LIBS 		= ./libft/libft.a
SRCS		= pipex.c pipex_utils.c manage_child.c
SRCS_BONUS	= pipex_bonus.c pipex_utils_bonus.c manage_child_bonus.c get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c

ifdef WITH_BONUS
	OBJS = $(SRCS_BONUS:.c=.o)
else
	OBJS = $(SRCS:.c=.o)
endif

all : $(NAME)

bonus : 
	make WITH_BONUS=1 all

$(NAME) : $(OBJS)
		@cd libft && $(MAKE)
		$(CC) $(CFLAG) $(OBJS) $(LIBS) -o $(NAME)

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAG) -c $< -o $@

clean :
	$(RM) $(SRCS_BONUS:.c=.o) $(SRCS:.c=.o)
	@cd libft && $(MAKE) clean

fclean : clean
	$(RM) $(NAME) $(LIBS)

re : fclean all

.PHONY : all clean fclean re