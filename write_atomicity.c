#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * thread_0(void *arg);
void * thread_1(void *arg);
void * thread_2(void *arg);

int A = 0;
int B = 0;
int counter = 0;

int main(int argc, char **argv) {
    int run_num = 50000;
    int j = 0;
    for (;j < run_num; j++) {
	int num_threads = 3;
	pthread_t tids[num_threads];

	// init thread 2
	pthread_attr_t attr2;
	pthread_attr_init(&attr2);
	pthread_create(&tids[2], &attr2, thread_2, NULL); 

	// init thread 1
	pthread_attr_t attr1;
	pthread_attr_init(&attr1);
	pthread_create(&tids[1], &attr1, thread_1, NULL); 

	// init thread 0
	pthread_attr_t attr0;
	pthread_attr_init(&attr0);
	pthread_create(&tids[0], &attr0, thread_0, NULL); 

	int i;
	for (i = 0; i < num_threads; i++) {
	    pthread_join(tids[i], NULL);
	}
	A = 0;
	B = 0;
    }
    printf("%d out of %d times the returned value was 1\n", counter, run_num);
    return 0;
}

void * thread_0(void *arg) {
    A = 1;
    // printf("t0 executed\n");
    pthread_exit(0);
}

void * thread_1(void *arg) {
    while (A == 0) { ; }
    B = 1;
    // printf("t1 executed\n");
    pthread_exit(0);
}

void * thread_2(void *arg) {
    while (B == 0) { ; }
    counter += A;
    // printf("%d\n", A);
    // printf("t2 executed\n");
    pthread_exit(0);
}
