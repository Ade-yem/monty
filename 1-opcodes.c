#include "monty.h"

/**
 * add - adds the data in the stack
 *
 * @doubly: head of the linked list
 * @cline: line number
 * Return: no return
 */

void add(stack_t **doubly, unsigned int cline)
{
	int i = 0;
	stack_t *tmp = *doubly;

	for (; tmp != NULL; tmp = tmp->next, i++)
		;
	if (i < 2)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", cline);
		free_v_glo();
		exit(EXIT_FAILURE);
	}
	tmp = (*doubly)->next;
	tmp->n += (*doubly)->n;
	pop(doubly, cline);
}

/**
 * nop - pushes an element to the stack
 *
 * @doubly: head of the linked list
 * @cline: line number
 * Return: no return
 */
void nop(stack_t **doubly, unsigned int cline)
{
	(void)doubly;
	(void)cline;
}

