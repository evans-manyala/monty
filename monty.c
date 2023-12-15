#include "monty.h"

/**
 * push_instruction - Pushes an element onto the stack.
 * @stack: Pointer to the stack.
 * @lineNum: Line number in the Monty file.
 */
void push_instruction(stack_t **stack, unsigned int lineNum)
{
	char argument[100];

	if (!fgets(argument, sizeof(argument), NULL))
	{
		fprintf(stderr, "Error: L%u: Missing argument for 'push'\n", lineNum);
		exit(1);
	}

	int value;

	if (kstrtol(argument, 0, 10, &value) != 0)
	{
		fprintf(stderr, "Error: L%u: Invalid argument '%s' for 'push'\n",
			lineNum, argument);
		exit(1);
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
