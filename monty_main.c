#include "monty.h"
#include <stdio.h>

/**
 * MAX_LINE_LENGTH - Maximum length of a line in the Monty bytecode file
 * Description: This constant defines the maximum number of characters
 * allowed in a line of the Monty bytecode file.
 */
#define MAX_LINE_LENGTH	1024

/**
 * main - Entry point for the Monty interpreter
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char *argv[])
{
	FILE *file;
	stack_t *stack = NULL;
	char line[MAX_LINE_LENGTH];
	unsigned int line_number = 0;
	char *opcode;
	void (*op_func)(stack_t **, unsigned int) = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), file) != NULL)
	{
		line_number++;
		opcode = strtok(line, " \t\n");
		if (opcode == NULL)
			continue;

		op_func = NULL;

		if (strcmp(opcode, "push") == 0)
			op_func = push;
		else if (strcmp(opcode, "pall") == 0)
			op_func = pall;
		else if (strcmp(opcode, "pint") == 0)
			op_func = pint;
		else if (strcmp(opcode, "pop") == 0)
			op_func = pop;
		else if (strcmp(opcode, "swap") == 0)
			op_func = swap;
		else if (strcmp(opcode, "add") == 0)
			op_func = add;
		else if (strcmp(opcode, "nop") == 0)
			op_func = nop;

		if (op_func == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			fclose(file);
			free_stack(&stack);
			exit(EXIT_FAILURE);
		}

		op_func(&stack, line_number);
	}

	fclose(file);
	free_stack(&stack);
	return (EXIT_SUCCESS);
}

