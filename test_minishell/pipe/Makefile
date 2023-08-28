# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 09:27:08 by yusekim           #+#    #+#              #
#    Updated: 2023/08/27 21:33:56 by dongseo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main_bonus.c \
		 check_input_bonus.c \
		 execute_cmds_bonus.c \
		 here_doc_bonus.c \

OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a


all: $(NAME)

$(LIBFT):
	cd libft ; $(MAKE)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) -o $(NAME) $^
	touch $@

clean :
	rm -f $(OBJS) $(B_OBJS)
	cd libft ; $(MAKE) clean

fclean : clean
	rm -f $(NAME) $(BONUS_NAME) MANDATORY_FLAG BONUS_FLAG
	cd libft ; $(MAKE) fclean

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all bonus clean fclean re

