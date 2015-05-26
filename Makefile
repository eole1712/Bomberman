CC		= g++

NAME		= bomberman

SRCSDIR		= srcs
GAMEDIR		= $(SRCSDIR)/game/
MISCDIR		= $(SRCSDIR)/misc/
COREDIR		= $(SRCSDIR)/core/
EXCEPTDIR	= $(SRCSDIR)/exceptions/
BUFFDIR		= $(GAMEDIR)/buffs/

CORESRCS	= main.cpp

GAMESRCS	= Player.cpp 		\
		  BuffTimer.cpp		\
		  Empty.cpp		\
		  ../server/Map.cpp	\
		  RessourceStock.cpp	\

BUFFSRCS	= BuffDecSpeed.cpp	\
		  BuffFactory.cpp	\
		  BuffIncBomb.cpp	\
		  BuffIncSpeed.cpp	\
		  BuffNoBomb.cpp	\
		  BuffParalyzed.cpp	\
		  BuffShield.cpp	\
		  BuffIncRange.cpp	\
		  IBuff.cpp		\

MISCSRCS	= Timer.cpp		\
		  my_random.cpp		\

EXCEPTSRCS	= ResourceUnavailable.cpp	\
		  LuaError.cpp			\
		  InvalidNbPlayers.cpp		\
		  InvalidDimensions.cpp		\

SRCS		+= $(addprefix $(COREDIR), $(CORESRCS))
SRCS		+= $(addprefix $(GAMEDIR), $(GAMESRCS))
SRCS		+= $(addprefix $(MISCDIR), $(MISCSRCS))
SRCS		+= $(addprefix $(BUFFDIR), $(BUFFSRCS))
SRCS		+= $(addprefix $(EXCEPTDIR), $(EXCEPTSRCS))

OBJS		= $(SRCS:.cpp=.o)

CXXFLAGS	+= -W -Wall -Werror -Wextra -g -std=c++11
CXXFLAGS	+= -I./$(SRCSDIR) -I./$(GAMEDIR) -I./$(COREDIR)
CXXFLAGS	+= -I./$(MISCDIR) -I./$(BUFFDIR) -I./$(EXCEPTDIR) -I./srcs/server/

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
