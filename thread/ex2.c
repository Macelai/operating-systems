#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void *t_print() {
	printf("Nova thread criada. TID = %d!\n", pthread_self());
}

int main(int argc, char const *argv[]) {
	int n_threads = atoi(argv[1]);
	pthread_t th[n_threads];
	for (size_t i = 0; i < n_threads; i++) {
		pthread_create(&th[i], NULL, t_print, NULL);
	}
	for (size_t i = 0; i < n_threads; i++) {
		pthread_join(th[i], NULL);
	}
	printf("the end\n");
	return 0;
}
