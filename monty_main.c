#include "monty.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    stack_t *stack = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1)
    {
        /* Tokenize the line and get the opcode */
        char *opcode = strtok(line, " \t\n");

        /* Ignore blank lines */
        if (opcode == NULL)
            continue;

        /* Find the corresponding function for the opcode */
        void (*op_func)(stack_t **, unsigned int) = NULL;
        if (strcmp(opcode, "push") == 0)
            op_func = push;
        else if (strcmp(opcode, "pall") == 0)
            op_func = pall;
        /* Add more opcode handlers as needed */

        /* If the opcode is not recognized, print an error and exit */
        if (op_func == NULL)
        {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
            free(line);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        /* Call the opcode handler function */
        op_func(&stack, line_number);
    }

    free(line);
    fclose(file);

    /* Free the stack if needed */

    return EXIT_SUCCESS;
}

