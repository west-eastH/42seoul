NAME = megaphone
CXX			= c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

RM			= rm -f
SRCS = megaphone.cpp
OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CXX) $(CFLAG) $(OBJS) -o $(NAME)

%.o : %.cpp
	$(CXX) $(CFLAG) -c $< -o $@

clean :
	$(RM) $(SRCS:.cpp=.o)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re