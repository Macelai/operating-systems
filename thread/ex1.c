#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void *t_print() {
	printf("Nova thread criada. TID = %u!\n", pthread_self());
}

int main(int argc, char **argv) {
	pthread_t thread;
	pthread_create(&thread, NULL, t_print, NULL);
	pthread_join(thread, NULL);
	return 0;
}
