OBJS	= Main.o Screen.o Input.o Shader.o Buffer.o Renderable.o Camera.o Texture.o Quad.o glad.o
SOURCE	= Main.cpp Screen.cpp Input.cpp Shader.cpp Buffer.cpp Renderable.cpp Camera.cpp Texture.cpp Quad.cpp glad/src/glad.c
#HEADER	=

ifeq ($(OS),Windows_NT)
OUT	= Graphics_Engine.exe
else
OUT	= Graphics_Engine
endif

CC	 = i686-w64-mingw32-g++
FLAGS	 = -g -c -Wall -Wno-unknown-pragmas -ISDL/include -ISDL_image/include -Iglad/include
LFLAGS	 = -ISDL/include -LSDL/lib -ISDL_image/include -LSDL_image/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32

all: $(OBJS)
	$(CC) -g $(OBJS) $(LFLAGS) -o $(OUT)

glad.o: glad/src/glad.c
	$(CC) $(FLAGS) glad/src/glad.c

Main.o: Main.cpp
	$(CC) $(FLAGS) Main.cpp 

Screen.o: Screen.cpp
	$(CC) $(FLAGS) Screen.cpp 

Input.o: Input.cpp
	$(CC) $(FLAGS) Input.cpp 

Shader.o: Shader.cpp
	$(CC) $(FLAGS) Shader.cpp 

Buffer.o: Buffer.cpp
	$(CC) $(FLAGS) Buffer.cpp 

Renderable.o: Renderable.cpp
	$(CC) $(FLAGS) Renderable.cpp 

Camera.o: Camera.cpp
	$(CC) $(FLAGS) Camera.cpp 

Texture.o: Texture.cpp
	$(CC) $(FLAGS) Texture.cpp 

Quad.o: Quad.cpp
	$(CC) $(FLAGS) Quad.cpp 

clean:
	$(RM) $(OUT) $(OBJS) 

