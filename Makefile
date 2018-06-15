SOURCEFILES=lasersFromSpace.cpp eventHandler.cpp ../gameEngine/window/initialization.cpp ../gameEngine/window/rendering.cpp ../gameEngine/window/viewport.cpp ../gameEngine/creatorTools/CreatorTools.cpp Bomb.cpp missiles.cpp gameStats.cpp ../gameEngine/collisionDetection/collisionDetection.cpp
TARGETFILE=lasers
LFLAGS=
CFLAGS=-lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf
COMPILER=g++
all:
	$(COMPILER) $(LFLAGS) -o $(TARGETFILE) $(SOURCEFILES) $(CFLAGS)
