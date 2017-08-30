#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char const *argv[]) {
	for (size_t i = 0; i < atoi(argv[1]); i++) {
		pid_t pid = fork();
		if (pid == 0) {
			c_sleep();
			break;
		}
	}
	while (wait(0) > -1);
	return 0;
}

void c_sleep() {
	time_t t;
	srand((unsigned) time(&t) * getpid());
	int c_time = ((rand() % 10) + 1);
	printf("Processo %i criado, irá dormir por %i \n", getpid(), c_time);
	sleep(c_time);
}
