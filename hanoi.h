#ifndef _HANOI_H
#define _HANOI_H

#include "stack.h"

struct action {
	int fromstack;
	int tostack;
};

typedef struct action action;

void hanoi_next(const int draws, const int disks, int *last, action *act, const stack const *pins);

#endif /* _HANOI_H */
