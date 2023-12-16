#include "monty.h"

/**
 * push_instruction - Pushes an element onto the stack.
 * @stack: Pointer to the stack.
 * @lineNum: Line number in the Monty file.
 */
void push_instruction(stack_t **stack, unsigned int lineNum)
{
	char argument[100], *endptr;
	int value, errno;

	if (!fgets(argument, sizeof(argument), NULL))
	{
		fprintf(stderr, "Error: L%u: Missing argument for 'push'\n", lineNum);
		exit(1);
	}

	errno = 0;
	value = strtol(argument, &endptr, 10);
	
	if (errno != 0 || *endptr != '\0')
	{
		fprintf(stderr, "Error: L%u: Invalid argument '%s' for 'push'\n", lineNum, argument);
		exit(EXIT_FAILURE);
	}


	stack_t *newNode = malloc(sizeof(stack_t));

	newNode->n = value;
	newNode->prev = NULL;
	newNode->next = *stack;
	*stack = newNode;
}

/**
 * pall_instruction - Prints all values in the stack.
 * @stack: Pointer to the stack.
 * @lineNum: Line number in the Monty file.
 */
void pall_instruction(stack_t **stack, unsigned int lineNum)
{
	if (*stack == NULL)
		return;
	stack_t *current = *stack;

	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * process_line - Function processes a line of Monty bytecode.
 * @line: The line to process.
 * @stack: Pointer to the stack.
 * @lineNum: Line number in the Monty file.
 */
void process_line(char *line, stack_t **stack, unsigned int *lineNum, instruction_t *instructions)
{
	int found = 0, x;
	char *opcode = strtok(line, " \t\n");

	if (!opcode)
		return;
	for (x = 0; x < sizeof(instructions) / sizeof(instructions[0]); x++)
	{
		if (!strcmp(opcode, instructions[x].opcode))
		{	
			instructions[x].f(stack, *lineNum);
			found = 1;
			break;
		}
	}
	if (!found)
	{
		fprintf(stderr, "Error: L%u: Unknown opcode '%s'\n", *lineNum, opcode);
		exit(EXIT_FAILURE);
	}
	(*lineNum)++;
}
/**
 * free_stack - Function frees the stack after completion.
 * @stack:  Pointer to pointer for the stack
*/
void free_stack(stack_t *stack)
{
	stack_t *current = stack;
	stack_t *next;
	
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(stack);
}

/**
 * main - Main Function of the program
 * @argc: Number of command-line arguments.
 * @argv: An Array of pointers to the command-line arguments.
 * Return: 0 if successful.
 */
int main(int argc, char **argv)
{
	unsigned int lineNum = 1;
	char *bytecode_file, line[100];
	FILE *fp;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <bytecode_file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	bytecode_file = argv[1];
	fp = fopen(bytecode_file, "r");

	if (!fp)
	{
		fprintf(stderr, "Error: Could not open file '%s'\n", bytecode_file);
		exit(EXIT_FAILURE);
	}
	instruction_t instructions[] = {
        {"push", push_instruction}, {"pall", pall_instruction
        },
};

	while (fgets(line, sizeof(line), fp) != NULL)
	{
		process_line(line, &stack, &lineNum, instructions);
	}
	fclose(fp);
	free_stack(stack);
	return (0);
}
