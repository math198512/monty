#include "monty.h"

/**
 * o_file - opens a file
 * @file_name: the file namepath
 * Return: void
 */

void o_file(char *file_name)
{
	FILE *fd = fopen(file_name, "r");

	if (file_name == NULL || fd == NULL)
		fprintf(stderr, "Error: Can't open file %s\n", file_name);

	r_file(fd);
	fclose(fd);
}

/**
 * r_file - reads a file
 * @fd: pointer to file descriptor
 * Return: void
 */

void r_file(FILE *fd)
{
	int line_number, format = 0;
	char *buffer = NULL;
	size_t len = 0;

	line_number = 1;
	while (getline(&buffer, &len, fd) != -1)
	{
		format = parsing(buffer, line_number, format);
		line_number++;
	}
	free(buffer);
}

/**
 * parsing - Separates each line into tokens
 * @buffer: line from the file
 * @line_number: line number
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */

int parsing(char *buffer, int line_number, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		fprintf(stderr, "Error: malloc failed\n");

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	func_finder(opcode, value, line_number, format);
	return (format);
}

/**
 * func_finder - find the appropriate function for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * @ln: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void func_finder(char *opcode, char *value, int ln, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", add_to_st},
		{"pall", print_st},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{NULL, NULL}
	};

	/*
	 * if (opcode[0] == '#')
	 * return;
	*/


	flag = 1;
	i = 0;
	while (func_list[i].opcode != NULL)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			fun_call(func_list[i].f, opcode, value, ln, format);
			flag = 0;
		}
		i++;
	}
	if (flag == 1)
		fprintf(stderr, "L%d: unknown instruction %s\n", ln, opcode);
}

/**
 * fun_call - Calls the required function.
 * @func: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @format: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void fun_call(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;/*val now points to val[1]*/
			flag = -1;
		}
		if (val == NULL)
			fprintf(stderr, "L%d: usage: push integer\n", ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				fprintf(stderr, "L%d: usage: push integer\n", ln);
		}
		node = create_node(atoi(val) * flag);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add_to_queue(&node, ln);
	}
	else
		func(&head, ln);
}

