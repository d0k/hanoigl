CC = gcc
CFLAGS = -pipe -ggdb -Wall -Wextra -Werror -Wno-unused-parameter -ansi -pedantic
LDFLAGS = -lGL -lGLU -lglut

OBJS=hanoi.o stack.o objects.o main.o 

hanoigl: $(OBJS)
	gcc $(LDFLAGS) $(OBJS) -o hanoigl

.PHONY clean:
	rm -f *.o hanoigl
