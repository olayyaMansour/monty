#include "monty.h"
#include <stdio.h>
void push(stack_t **stack, unsigned int line_number)
{
	char *token;
	int value;
	stack_t *new_node;

	token = strtok(NULL, " \t\n");
	if (token == NULL || !isdigit(*token))
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	value = atoi(token);

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = value;
	new_node->prev = NULL;
	if (*stack != NULL)
		(*stack)->prev = new_node;
	new_node->next = *stack;
	*stack = new_node;
}

