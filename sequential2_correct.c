#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * thread_0(void *arg);
void * thread_1(void *arg);

int A = 0;
int B = 0;
int result = 0;

int main(int argc, char **argv) {
    int counter = 0;
    while (1) {

	pthread_t tids[2];

	// init thread 1
	pthread_attr_t attr1;
	pthread_attr_init(&attr1);
	pthread_create(&tids[1], &attr1, thread_1, NULL); 

	// init thread 0
	pthread_attr_t attr0;
	pthread_attr_init(&attr0);
	pthread_create(&tids[0], &attr0, thread_0, NULL); 

	pthread_join(tids[0], NULL);
	pthread_join(tids[1], NULL);
	
	if (result == 1) {
	    printf("The machine is not SC, exited at loop iteration #%d.\n", counter);
	    break;
	}
	printf("Iteration #%d\n", counter);

	A = 0;
	B = 0;
	result = 0;
	counter++;
    }
    return 0;
}

void * thread_0(void *arg) {
    A = 1;
    B = 1;
    pthread_exit(0);
}

void * thread_1(void *arg) {
    while (A == 0 || B == 0) { 
	int b = B;
	int a = A;
	if (a == 0 && b == 1) {
	    printf("A = %d, B = %d\n", a, b);
	    result = 1;
	}
    }
    pthread_exit(0);
}
