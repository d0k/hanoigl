#include <math.h>

#include "hanoigl.h"
#include "hanoi.h"

void hanoi_next(const int draws, const int disks, int *last, action *act, const stack *pins)
{
	if (!(pins[0].top == NULL && pins[1].top == NULL)) {
		if (draws%2 == 0) {
			act->fromstack = *last;
			if (disks%2 == 1)
				*last = (*last+2)%3;
			else
				*last = (*last+1)%3;

			act->tostack = *last;
		} else {
			int pin1 = (*last+1)%3;
			int pin2 = (*last+2)%3;
			disk *d1 = pins[pin1].top;
			disk *d2 = pins[pin2].top;

			GLfloat radius1 = d1 != NULL ? d1->radius : INFINITY;
			GLfloat radius2 = d2 != NULL ? d2->radius : INFINITY;
			if (radius1 < radius2) {
				act->fromstack = pin1;
				act->tostack = pin2;
			} else {
				act->fromstack = pin2;
				act->tostack = pin1;
			}
		}
	} else {
		act->fromstack = act->tostack = -1;
	}
}
