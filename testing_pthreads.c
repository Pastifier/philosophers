#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static void routine(void* num);
volatile __sig_atomic_t sig = 0;

int main(void) {
	pthread_t threads[12];

	for (int i = 0; i < 12; i++) {
		void* num = &i;
		pthread_create(&threads[i], NULL, (void *)routine, num);
	}
	for (int i = 0; i < 12; i++) {
		pthread_join(threads[i], NULL);
	}
	return (0);
}

static void routine(void* num) {
	int number = *((int*)num);
	printf("%d\n", number);
	for (int i = 0; i < 100000000; i++)
		;
}
