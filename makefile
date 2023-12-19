main = main.cpp
main_obj = main.o
exec = dist/arsenic.exe
INC = -Iinc
TAG = -lmingw32 -lopengl32 -lglfw3 -lgdi32 -lglew32 -lglu32
LIB = -Llib
windows:
	g++ -c $(main) $(INC)
	g++ -o  $(exec) $(main_obj) $(LIB) $(TAG)
	./$(exec)
