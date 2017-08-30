#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	fork();
	printf("Novo processo criado\n");
	return 0;
}
