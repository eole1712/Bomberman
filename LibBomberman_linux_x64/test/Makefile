
NAME = test

SRC = bra.cpp

OBJ = $(SRC:.cpp=.o)

INCLUDESPATH = ../includes/

LIBPATH = ../libs/

LIBS = -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread

CC = g++

CXXFLAGS = -Wall -Wextra  -I $(INCLUDESPATH)

all: $(NAME)
	export LD_LIBRARY_PATH=~/rendu/cpp_bomberman/LibBomberman_linux_x64/libs/

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -L $(LIBPATH) $(LIBS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
