#include "monty.h"

/**
 * swap_nodes - Swaps the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: Interger representing the line number of of the opcode.
 */
void swap_nodes(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		fprintf(stderr, "L%d: can't %s, stack too short\n", line_number, "swap");
	tmp = (*stack)->next;
	(*stack)->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = *stack;
	tmp->next = *stack;
	(*stack)->prev = tmp;
	tmp->prev = NULL;
	*stack = tmp;
}

/**
* push - Pushes an element to the stack
* @stack: stack
* @n: number
* Return: void
*/

void push(stack_t **stack, unsigned int n)
{
	stack_t *new = NULL;

	new = malloc(sizeof(stack_r));

	if (new == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new->n = n;
	new->next = *stack;
	new->prev = NULL;

	if (*stack != NULL)
	{
		(*stack)->prev = new;
	}
	*stack = new;
}

/**
* pall - prints the stack
* @stack: stack
* @line_number: line number
* Return: void
*/

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;
	(void)line_number;

	if (!stack)
	{
		fprintf(stderr, "L%d: Stack is empty\n", line_number);
		return;
	}

	while (tmp)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}

}
