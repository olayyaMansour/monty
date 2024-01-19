#include "monty.h"
#include <stdio.h>

#define MAX_LINE_LENGTH 1024

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
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        line_number++;

        /* Tokenize the line and get the opcode */
        opcode = strtok(line, " \t\n");

        /* Ignore blank lines */
        if (opcode == NULL)
            continue;

        /* Find the corresponding function for the opcode */
        op_func = NULL;
        if (strcmp(opcode, "push") == 0)
            op_func = push;
        else if (strcmp(opcode, "pall") == 0)
            op_func = pall;
        /* Add more opcode handlers as needed */

        /* If the opcode is not recognized, print an error and exit */
        if (op_func == NULL)
        {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        /* Call the opcode handler function */
        op_func(&stack, line_number);
    }

    fclose(file);

    /* Free the stack if needed */

    return EXIT_SUCCESS;
}

