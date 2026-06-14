CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

NAME = convert

SRCS = main.cpp  ScalarConverter.cpp  convertTools.cpp

OBJS = ${SRCS:%.cpp=%.o}

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re