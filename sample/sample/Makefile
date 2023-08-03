NAME = sample
INCLUDES	= ./sample.h
CC			= cc
CFLAG		= -Wall -Wextra -Werror

RM			= rm -f

LIBS 		= ./libft/libft.a
SRCS		= sample.c
SRCS_BONUS	= 

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