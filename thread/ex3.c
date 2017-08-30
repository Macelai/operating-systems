#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

int global = 0;

void *inc() {
	for (size_t i = 0; i < 100; i++) {
 		global++;
	}
}

int main(int argc, char const *argv[]) {
	int n_threads = atoi(argv[1]);
	pthread_t th[n_threads];
	for (size_t i = 0; i < n_threads; i++) {
		pthread_create(&th[i], NULL, inc, NULL);
	}
	for (size_t i = 0; i < n_threads; i++) {
		pthread_join(th[i], NULL);
	}
	printf("Global: %d\n", global);
	return 0;
}
