#include "monty.h"

void push_instruction(stack_t **stack, unsigned int line_number)
{
	char argument[100];

	if (!fgets(argument, sizeof(argument), NULL))
	{
		fprintf(stderr, "Error: L%u: Missing argument for 'push'\n", line_number);
		exit(1);
	}

	int value;

	if (sscanf(argument, "%d", &value) != 1)
	{
		fprintf(stderr, "Error: L%u: Invalid argument '%s' for 'push'\n",
		line_number, argument);
		exit(1);
	}

	stack_t *newNode = malloc(sizeof(stack_t));
	newNode->n = value;
	newNode->prev = NULL;
	newNode->next = *stack;
	*stack = newNode;
}

void pall_instruction(stack_t **stack, unsigned int line_number)
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
