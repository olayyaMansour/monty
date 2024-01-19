#include "monty.h"
/**
 * pall - Print all elements of the stack
 * @stack: Pointer to the stack
 * @line_number: Line number in the Monty bytecode file
 */
void print_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *current_node;

	(void)line_number; // Unused parameter

	current_node = *stack;

	if (current_node == NULL)
		return;

	while (current_node)
	{
		printf("%d\n", current_node->n);
		current_node = current_node->next;
	}
}
