CC		= g++

NAME		= bomberman

SRCSDIR		= srcs/
GAMEDIR		= $(SRCSDIR)/game/
MISCDIR		= $(SRCSDIR)/misc/
COREDIR		= $(SRCSDIR)/core/

SRCS		= main.cpp

OBJS		= $(addprefix $(SRCSDIR), $(SRCS:.cpp=.o))

CXXFLAGS	+= -W -Wall -Werror -Wextra -g #-std=c++11
CXXFLAGS	+= -I./$(SRCSDIR)

LDFLAGS		+= -pthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
