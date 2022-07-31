linux:
	g++ -c *.c
	g++ -o arsenic main.o -lGLEW -lSDL2 -lGL -lGLU -lglut

