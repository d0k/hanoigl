#ifndef _STACK_H
#define _STACK_H

struct disk {
	char color;
	GLfloat radius;
	struct disk *next;
	struct disk *prev;
};

typedef struct disk disk;

struct stack {
	disk *bottom;
	disk *top;
};

typedef struct stack stack;

void push(stack *pin, disk *item);
disk *pop(stack *pin);

#endif /* _STACK_H */
