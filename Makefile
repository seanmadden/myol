all:
	gcc -std=c99 -Wall -ledit prompt.c dependencies/mpc.c -lm -o prompt
