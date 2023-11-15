#include "monty.h"

/**
* main - monty code interpreter
* @argc: argc
* @argv: argv
* Return: return
*/
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
