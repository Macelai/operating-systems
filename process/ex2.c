#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
	for (size_t i = 0; i < 4; i++) {
		pid_t pid = fork();
		if (pid > 0) {
			printf("Processo pai %i criou %i\n", getpid(), pid);
			wait(NULL);
		}
		else {
			printf("Processo filho %i\n", getpid());
			break;
		}
	}
	return 0;
}
