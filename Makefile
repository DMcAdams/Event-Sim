# build an executable named myprog from myprog.c
all: main.c
	gcc -o main main.c

clean:
	$(RM) main
