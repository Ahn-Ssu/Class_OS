.SUFFIXES = .c .o

CC = gcc

PROGRAM: hw4_1 hw4_2 hw4_3a hw4_3b

all: $(PROGRAM)

HW4_1_SRC	= hw4_1.c Console.c
HW4_2_SRC	= hw4_2.c KeyBuffer.c Console.c
HW4_3a_SRC	= hw4_3a.c KeyBuffer.c Console.c
HW4_3b_SRC	= hw4_3b.c KeyBuffer.c Console.c

HW4_1_OBJ = ${HW4_1_SRC:.c=.o}
HW4_2_OBJ = ${HW4_2_SRC:.c=.o}
HW4_3a_OBJ = ${HW4_3a_SRC:.c=.o}
HW4_3b_OBJ = ${HW4_3b_SRC:.c=.o}

hw4_1: $(HW4_1_OBJ)
	$(CC) $(HW4_1_OBJ) -o $@

hw4_2: $(HW4_2_OBJ)
	$(CC) $(HW4_2_OBJ) -o $@ 

hw4_3a: $(HW4_3a_OBJ)
	$(CC) $(HW4_3a_OBJ) -o $@ -lrt

hw4_3b: $(HW4_3b_OBJ)
	$(CC) $(HW4_3b_OBJ) -o $@ -lrt


.c.o:
	$(CC) -c $<

clean:
	rm hw4_1 hw4_2 hw4_3a hw4_3b *.o
