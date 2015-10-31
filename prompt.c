#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>

int main(int argc, char** argv) {
	
	//Print latest version
	puts("Lispy Version 0.0.0.1");
	puts("Press Ctrl-c to exit\n");

	while (1) {
		char* input = readline("lispy> ");
		add_history(input);

		printf("No you're a %s\n", input);

		free(input);
	}

	return 0;
}
