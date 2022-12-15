#include "monty.h"

/**
 * push - pushes an element to the stack
 *
 * @stack: head of the linked list
 * @line_number: line number
 * Return: no return
 */

void push(stack_t **stack, unsigned int line_number)
{
	int i, j;

	if (!v_glo.arg)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		free_v_glo();
		exit(EXIT_FAILURE);
	}
	for (i = 0; v_glo.arg[i] != '\0'; i++)
	{
		if (!isdigit(v_glo.arg[i]) && v_glo.arg[i] == '-')
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_number);
			free_v_glo();
			exit(EXIT_FAILURE);
		}
	}
	j = atoi(v_glo.arg);
	if (v_glo.lifo == 1)
		add_dnodeint(stack, j);
	else
		add_dnodeint_end(stack, j);
}


/**
 * pall - prints all values on the stack
 *
 * @doubly: head of the linked list
 * @cline: line numbers
 * Return: no return
 */
void pall(stack_t **doubly, unsigned int cline)
{
	stack_t *temp;
	(void)cline;

	temp = *doubly;

	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

/**
 * pint - prints the value at the top of the stack
 *
 * @doubly: head of the linked list
 * @cline: line number
 * Return: no return
 */
void pint(stack_t **doubly, unsigned int cline)
{
	(void)cline;

	if (*doubly == NULL)
	{
		fprintf(stderr, "L%u: ", cline);
		fprintf(stderr, "can't pint, stack empty\n");
		free_v_glo();
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*doubly)->n);
}

/**
 * pop - removes the top element of the stack
 *
 * @doubly: head of the linked list
 * @cline: line number
 * Return: no return
 */
void pop(stack_t **doubly, unsigned int cline)
{
	stack_t *tmp;

	if (doubly == NULL || *doubly == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", cline);
		free_v_glo();
		exit(EXIT_FAILURE);
	}
	tmp = *doubly;
	*doubly = (*doubly)->next;
	free(tmp);
}

/**
 * swap - swaps the top two elements of the stack
 *
 * @doubly: head of the linked list
 * @cline: line number
 * Return: no return
 */
void swap(stack_t **doubly, unsigned int cline)
{
	int m = 0;
	stack_t *aux = NULL;

	aux = *doubly;

	for (; aux != NULL; aux = aux->next, m++)
		;

	if (m < 2)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", cline);
		free_v_glo();
		exit(EXIT_FAILURE);
	}

	aux = *doubly;
	*doubly = (*doubly)->next;
	aux->next = (*doubly)->next;
	aux->prev = *doubly;
	(*doubly)->next = aux;
	(*doubly)->prev = NULL;
}
