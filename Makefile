CC		= g++

NAME		= bomberman

SRCSDIR		= srcs
GAMEDIR		= $(SRCSDIR)/game/
MISCDIR		= $(SRCSDIR)/misc/
COREDIR		= $(SRCSDIR)/core/
EXCEPTDIR	= $(SRCSDIR)/exceptions/
BUFFDIR		= $(GAMEDIR)/buffs/
BOMBDIR		= $(GAMEDIR)/bombs/
GDLDIR		= $(SRCSDIR)/LibBomberman_linux_x64/

CORESRCS	= main.cpp		\
		  Game.cpp		\
		  Asset3d.cpp		\
		  Object3d.cpp		\
		  CameraObject.cpp	\

GAMESRCS	= Player.cpp 		\
		  BuffTimer.cpp		\
		  Empty.cpp		\
		  ../server/Map.cpp	\
		  RessourceStock.cpp	\
		  BombTimer.cpp		\
		  Spawn.cpp		\
		  Wall.cpp		\
		  DestroyableWall.cpp	\
		  IObject.cpp		\

BUFFSRCS	= BuffDecSpeed.cpp	\
		  BuffFactory.cpp	\
		  BuffIncBomb.cpp	\
		  BuffIncSpeed.cpp	\
		  BuffNoBomb.cpp	\
		  BuffParalyzed.cpp	\
		  BuffShield.cpp	\
		  BuffIncRange.cpp	\
		  IBuff.cpp		\

BOMBSRCS	= BombClassic.cpp	\
		  IBomb.cpp		\


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
SRCS		+= $(addprefix $(BOMBDIR), $(BOMBSRCS))
SRCS		+= $(addprefix $(EXCEPTDIR), $(EXCEPTSRCS))

OBJS		= $(SRCS:.cpp=.o)

CXXFLAGS	+= -W -Wall -Werror -Wextra -g -std=c++11
CXXFLAGS	+= -I./$(SRCSDIR) -I./$(GAMEDIR) -I./$(COREDIR) -I./$(BOMBDIR)
CXXFLAGS	+= -I./$(MISCDIR) -I./$(BUFFDIR) -I./$(EXCEPTDIR) -I./srcs/server/
CXXFLAGS	+= -I./$(GDLDIR)/includes/

LDFLAGS		+= -pthread -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2

all: $(NAME)
     export LD_LIBRARY_PATH=~/rendu/cpp_bomberman/srcs/LibBomberman_linux_x64/libs/


$(NAME): $(OBJS)
	 $(CC) -o $(NAME) $(OBJS) -L $(GDLDIR)/libs/ $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
