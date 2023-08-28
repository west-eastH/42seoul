#-------------------------------------------

BLACK       =   "\033[0;30m"
GRAY        =   "\033[1;30m"
RED         =   "\033[1;31m"
GREEN       =   "\033[0;32m"
YELLOW      =   "\033[1;33m"
PURPLE      =   "\033[0;35m"
CYAN        =   "\033[1;36m"
WHITE       =   "\033[1;37m"
EOC         =   "\033[0;0m"
LINE_CLEAR  =   "\x1b[1A\x1b[M"

#-------------------------------------------

NAME = minishell
CC = cc
CFLAGS = -I./include -Wall -Wextra -Werror -g
SRCS = ./main.c \
		./print_test.c \
		./env_utils.c \
		./lexer/lexer.c \
		./lexer/lexer_utils.c \
		./parser/parser.c \
		./parser/parser_utils.c \
		./parser/expand_utils.c \
		./executor/executor.c \
		./executor/pipe.c \

OBJS = $(SRCS:.c=.o)
# LINKING_FLAG = -lreadline -L${HOME}/homebrew/opt/readline/lib
# COMFILE_FLAGS = -I${HOME}/homebrew/opt/readline/include
LINKING_FLAG	= -lreadline -L${HOME}/goinfre/.brew/opt/readline/lib
COMFILE_FLAGS	= -I${HOME}/goinfre/.brew/opt/readline/include
# LINKING_FLAG	= -lreadline -L${HOME}/.brew/opt/readline/lib
# COMFILE_FLAGS	= -I${HOME}/.brew/opt/readline/include
LIBFT = ./libft/libft.a

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(LINKING_FLAG) -o $(NAME) $^
	@echo $(GREEN)"\n==========================================================\n"$(EOC)
	@echo $(YELLOW)"                    MINISHELL IS READY"$(EOC)
	@echo $(GREEN)"\n==========================================================\n"$(EOC)

$(LIBFT) :
	@cd libft ; $(MAKE)

%.o : %.c
	@$(CC) $(CFLAGS) $(COMFILE_FLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)
	cd libft ; $(MAKE) clean

fclean : clean
	rm -f $(NAME)
	cd libft ; $(MAKE) fclean

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all bonus clean fclean re
