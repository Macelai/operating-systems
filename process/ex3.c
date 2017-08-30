#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
	for (size_t i = 0; i < 2; i++) {
		pid_t pid = fork();
		if (pid > 0) {
			wait(0);
		}
		else {
			printf("Processo %i filho de %i\n", getpid(), getppid());
			for (size_t i = 0; i < 2; i++) {
				pid_t pid0 = fork();
				if (pid0 == 0) {
					printf("Processo %i filho de %i\n", getpid(), getppid());
					break;
				}
			}
			break;
		}
	}
	return 0;
}
