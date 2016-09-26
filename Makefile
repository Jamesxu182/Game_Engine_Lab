# OBJS specifies which files to compile as part of the project
OBJS = main.cpp

# CC specifies which compiler we're using
CC = g++

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

# LINKER_FLAGS specifies the libraries we're linking against
# Cocoa, IOKit, and CoreVideo are needed for static GLFW3.
LINKER_FLAGS = -lSDL2 -lSDL2main

OBJ_NAME = main

#This is the target that compiles our executable
$(OBJ_NAME): GameComponent.o Player.o Game.o main.o Bullet.o
	$(CC) GameComponent.o Bullet.o Player.o Game.o main.o $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

main.o: main.cpp Player.h GameComponent.h Game.h
	${CC} -c main.cpp -o main.o

Game.o: Game.cpp Game.h
	${CC} -c Game.cpp -o Game.o

Player.o: Player.cpp Player.h Game.h Bullet.h
	${CC} -c Player.cpp -o Player.o

Bullet.o: Bullet.h Bullet.cpp Game.h
	${CC} -c Bullet.cpp -o Bullet.o

GameComponent.o: GameComponent.cpp GameComponent.h
	$(CC) -c GameComponent.cpp -o GameComponent.o

clean:
	rm *.o $(OBJ_NAME)
