CC = c++ -std=c++98 -Wall -Werror -Wextra
SRC = array_bag.cpp  main.cpp  searchable_array_bag.cpp  searchable_tree_bg.cpp  set.cpp  tree_bag.cpp
OBJ = ${SRC:%.cpp=%.o}


%.o: %.cpp
	$(CC) -c $< -o $@

all: $(OBJ)
	$(CC) $(OBJ) -o a.out

clear: 
	rm -f a.out $(OBJ)

re: clear all