# build an executable named main
all: main.c
	gcc -o main main.c

clean:
	$(RM) main
