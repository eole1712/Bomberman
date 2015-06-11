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
TMPDIR		= $(GDLDIR)/test/
VENDORSDIR	= $(SRCSDIR)/vendors/
LUADIR		= $(VENDORSDIR)/lua-5.3.0/
LUABDIR		= $(VENDORSDIR)/LuaBridge/
LUAINCS		= $(LUADIR)/include/

CORESRCS	= main.cpp		\
		  Asset3d.cpp		\
		  Object3d.cpp		\
		  CameraObject.cpp	\
		  JSONDoc.cpp		\
		  ScoreList.cpp		\
		  MapList.cpp		\
		  Animation.cpp		\
		  Core.cpp		\

GAMESRCS	= Player.cpp 		\
		  Gamer.cpp		\
		  PlayerAI.cpp		\
		  BuffTimer.cpp		\
		  Empty.cpp		\
		  Map.cpp		\
		  AIStateMap.cpp	\
		  RessourceStock.cpp	\
		  BombTimer.cpp		\
		  Spawn.cpp		\
		  Wall.cpp		\
		  DestroyableWall.cpp	\
		  IObject.cpp		\
		  Color.cpp		\
		  Fire.cpp		\
		  Score.cpp		\
		  Sound.cpp		\

BUFFSRCS	= BuffDecSpeed.cpp	\
		  BuffFactory.cpp	\
		  BuffIncBomb.cpp	\
		  BuffIncSpeed.cpp	\
		  BuffNoBomb.cpp	\
		  BuffWeapon.cpp	\
		  BuffParalyzed.cpp	\
		  BuffShield.cpp	\
		  BuffIncRange.cpp	\
		  IBuff.cpp		\

BOMBSRCS	= BombClassic.cpp	\
		  BombVirus.cpp		\
		  IBomb.cpp		\
		  BombMine.cpp		\
		  BombBarrel.cpp		\
		  BombFactory.cpp	\

MENUSRCS	= AMenuObject.cpp	\
		  MenuGrid.cpp		\
		  Text2d.cpp		\
		  View2d.cpp		\

MISCSRCS	= Timer.cpp		\
		  my_random.cpp		\
		  StringConversion.cpp	\
		  LuaScript.cpp		\

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
SRCS		+= $(addprefix $(TMPDIR), $(MENUSRCS))

OBJS		= $(SRCS:.cpp=.o)

CXXFLAGS	+= -W -Wall -Werror -Wextra -o3 -std=c++11
CXXFLAGS	+= -I./$(SRCSDIR) -I./$(GAMEDIR) -I./$(COREDIR) -I./$(BOMBDIR)
CXXFLAGS	+= -I./$(MISCDIR) -I./$(BUFFDIR) -I./$(EXCEPTDIR) -I./srcs/server/
CXXFLAGS	+= -I./$(GDLDIR)/includes/ -I./$(COREDIR)/rapidjson -I ./$(TMPDIR)
CXXFLAGS	+= -I./$(LUABDIR) -I./$(LUABDIR)/detail -I./$(LUAINCS)

LDFLAGS		+= -L $(GDLDIR)/libs/ -L $(LUADIR)/lib
LDFLAGS		+= -pthread -lgdl_gl -lGL -lGLEW -lrt -lfbxsdk -lSDL -lSDL2 -ldl -llua -lvlc

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
