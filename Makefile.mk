OBJS	= Main.o Screen.o
SOURCE	= Main.cpp Screen.cpp
#HEADER	=

ifeq ($(OS),Windows_NT)
OUT	= Graphics_Engine.exe
else
OUT	= Graphics_Engine
endif

CC	 = i686-w64-mingw32-g++
FLAGS	 = -g -c -Wall -Wno-unknown-pragmas -ISDL/include
LFLAGS	 = -ISDL/include -LSDL/lib -lmingw32 -lSDL2main -lSDL2 -lopengl32

# libmingw32

all: $(OBJS)
	$(CC) -g $(OBJS) $(LFLAGS) -o $(OUT)

Main.o: Main.cpp
	$(CC) $(FLAGS) Main.cpp 

Screen.o: Screen.cpp
	$(CC) $(FLAGS) Screen.cpp 

clean:
	$(RM) $(OUT) $(OBJS) 

