CC = g++

BIN = bin/

OUT = main

FILES = main.cpp core/window/window.cpp vendor/glad/glad.c core/renderer/renderer.cpp core/shader/shader.cpp core/error/error.cpp

INC = core/

INC2 = vendor/

INC3 = /usr/include/SDL

INC4 = utils

INC5 = /usr/include/GL

LIBS = -lGLEW -lEGL -lGL -lGLU -lOpenGL -lSDL2 -lm

# TODO add seperate compilation for engine and app
all:
	$(CC) -I$(INC) -I$(INC2) -I$(INC3) -I$(INC4) -I$(INC5)  $(FILES) -o $(BIN)/$(OUT) $(LIBS)

