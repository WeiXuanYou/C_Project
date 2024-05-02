CC = gcc
CFLAGS = -lm -Wall
OBJ = homework.o function.o
EXE = run

all: $(EXE)
.c.o:; $(CC) -c $*.c

$(EXE):$(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	rm -rf $(EXE) *.o *.d core