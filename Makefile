CC		= g++

NAME		= bomberman

SRCSDIR		= srcs/
GAMEDIR		= $(SRCSDIR)/game/
MISCDIR		= $(SRCSDIR)/misc/
COREDIR		= $(SRCSDIR)/core/

BUFFDIR		= $(GAMEDIR)/buffs/

CORESRCS	= main.cpp
GAMESRCS	= #Player.cpp # tea to grisha -> ton player compile pas :p
BUFFSRCS	= BuffFactory.cpp
MISCSRCS	= Timer.cpp

SRCS		+= $(addprefix $(COREDIR), $(CORESRCS))
SRCS		+= $(addprefix $(GAMEDIR), $(GAMESRCS))
SRCS		+= $(addprefix $(MISCDIR), $(MISCSRCS))
SRCS		+= $(addprefix $(BUFFDIR), $(BUFFSRCS))

OBJS		= $(SRCS:.cpp=.o)

CXXFLAGS	+= -W -Wall -Werror -Wextra -g -std=c++11
CXXFLAGS	+= -I./$(SRCSDIR) -I./$(GAMEDIR) -I./$(COREDIR) -I./$(MISCDIR) -I./$(BUFFDIR)

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
