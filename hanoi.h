#ifndef _HANOI_H
#define _HANOI_H

struct action {
	char fromstack;
	char tostack;
	struct action *next;
};

typedef struct action action;

struct actions {
	action *head;
	action *tail;
};

typedef struct actions actions;

void hanoi(actions *queue, const int n, const char pin1, const char pin2, const char pin3);

#endif /* _HANOI_H */
