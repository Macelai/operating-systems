#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>

int global = 0;
sem_t semaphore;

void *inc() {
	for (size_t i = 0; i < 100; i++) {
		sem_wait(&semaphore);
 		global++;
		sem_post(&semaphore);
	}
}

int main(int argc, char const *argv[]) {
	int n_threads = atoi(argv[1]);
	pthread_t th[n_threads];
	sem_init(&semaphore, 0, 1);
	for (size_t i = 0; i < n_threads; i++) {
		pthread_create(&th[i], NULL, inc, NULL);
	}
	for (size_t i = 0; i < n_threads; i++) {
		pthread_join(th[i], NULL);
	}
	printf("Global: %d\n", global);
	return 0;
}
