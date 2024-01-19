#include "monty.h"
/**
 * push - Pushes an element onto the stack
 * @stack: Pointer to the stack
 * @line_number: Line number in the Monty bytecode file
 */
void push(stack_t **stack, unsigned int line_number)
{
	int value, index = 0;

	if (!bus.arg)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		fclose(bus.file);
		free(bus.content);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	if (bus.arg[0] == '-')
		index++;

	while (bus.arg[index] != '\0')
	{
		if (bus.arg[index] < '0' || bus.arg[index] > '9')
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			fclose(bus.file);
			free(bus.content);
			free_stack(*stack);
			exit(EXIT_FAILURE);
		}
		index++;
	}

	value = atoi(bus.arg);
	if (bus.lifo == 0)
		add_node_to_stack(stack, value);
	else
		add_node_to_queue(stack, value);
}

