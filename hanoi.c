#include "hanoigl.h"
#include "hanoi.h"

/*hanoi(3, 1, 2, 3);*/
/*
void hanoi(int n, int pin1, int pin2, int pin3) {
	if(n > 0) {
		hanoi(n-1, pin1, pin3, pin2);
		printf("Verschiebe von %d nach %d.\n", pin1, pin3);
		hanoi(n-1, pin2, pin1, pin3);
	}
}
*/

void hanoi(actions *queue, const int n, const char pin1, const char pin2, const char pin3) {
	action *curaction;
	if(n > 0) {
		hanoi(queue, n-1, pin1, pin3, pin2);

		/* push action into action queue */
		curaction = (action *)malloc(sizeof(action));
		curaction->next = NULL;
		curaction->fromstack = pin1;
		curaction->tostack = pin3;

		if(queue->head == NULL)
			queue->head = curaction;
		if(queue->tail != NULL)
			queue->tail->next = curaction;
		queue->tail = curaction;

		hanoi(queue, n-1, pin2, pin1, pin3);
	}
}
