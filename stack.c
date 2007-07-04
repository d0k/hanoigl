#include "hanoigl.h"
#include "stack.h"

/* item auf stapel legen */
void push(stack *pin, disk *item) {
	item->next = NULL;
	if(pin->bottom == NULL) {
		pin->bottom = item;
		pin->top = item;
		item->prev = NULL;
	} else {
		pin->top->next = item;
		item->prev = pin->top;
		pin->top = item;
	}
}

/* item von stapel herunternehmen */
disk *pop(stack *pin) {
	disk *tmp;
	if(pin->top != NULL) {
		tmp = pin->top;
		if(pin->top->prev != NULL) {
			pin->top->prev->next = NULL;
			pin->top = tmp->prev;
		} else {
			pin->bottom = NULL;
			pin->top = NULL;
		}
		return tmp;
	}
	return NULL;
}
