all:
	gcc -std=c99 -Wall -ledit prompt.c dependencies/mpc.c lval_core.c -lm -o prompt
