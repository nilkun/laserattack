SOURCEFILES=main.cpp eventHandler.cpp imageCreator.cpp screen.cpp screenRenderer.cpp Bomb.cpp missiles.cpp gameStats.cpp collisionDetection.cpp
TARGETFILE=play
LFLAGS=
CFLAGS=-lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf
COMPILER=g++
all:
	$(COMPILER) $(LFLAGS) -o $(TARGETFILE) $(SOURCEFILES) $(CFLAGS)
