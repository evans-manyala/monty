#ifndef MONTY_H
#define MONTY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int lineNum);
} instruction_t;

void function_push(stack_t **head, unsigned int num);
void function_pall(stack_t **head, unsigned int num);
void free_stack(stack_t *head);
void function_swp(stack_t **head, unsigned int counter);
void function_addQ(stack_t **head, int num);
void function_stack(stack_t **head, unsigned int counter);
void function_div(stack_t **head, unsigned int counter);
void function_mul(stack_t **head, unsigned int counter);
void function_pchar(stack_t **head, unsigned int counter);
void function_rotl(stack_t **head, unsigned int counter);
void function_pint(stack_t **head, unsigned int num);
void function_pop(stack_t **head, unsigned int counter);
void function_add(stack_t **head, unsigned int counter);
void function_nop(stack_t **head, unsigned int counter);
void function_sub(stack_t **head, unsigned int counter);
void function_mod(stack_t **head, unsigned int counter);
void function_pstr(stack_t **head, unsigned int counter);
void function_rotr(stack_t **head, __attribute__((unused)) unsigned int counter);
void function_addnode(stack_t **head, int n);
void function_Q(stack_t **head, unsigned int counter);
char *clear_line(char *content);
char *realloc(char *ptr, unsigned int oldSize, unsigned int newSize);
ssize_t getstdin(char **lineptr, int file);
int execute(char *content, stack_t **head, unsigned int counter, FILE *file);

#endif
