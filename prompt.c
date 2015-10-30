#include <stdio.h>

// Input buffer
const int BUFFER_SIZE = 2048;
static char buffer[BUFFER_SIZE];

int main(int argc, char** argv) {
	
	//Print latest version
	puts("Lispy Version 0.0.0.1");
	puts("Press Ctrl-c to exit\n");

	while (1) {
		fputs("lispy> ", stdout);

		fgets(buffer, BUFFER_SIZE, stdin);

		printf("No you're a %s", buffer);
	}

	return 0;
}
