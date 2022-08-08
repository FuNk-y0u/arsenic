CC = gcc
SRC = src/*.c
A_SRC = src/*.c
OBJ = *.o
OUT = liba.a

win:
	$(CC) -c $(A_SRC)
	ar rcs $(OUT) $(OBJ)
