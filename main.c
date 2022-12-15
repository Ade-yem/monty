#include "monty.h"

global_t v_glo;

/**
 * start_v_glo - initializes the global variables
 *
 * @fd: file descriptor
 * Return: no return
 */

void start_v_glo(FILE *fd)
{
	v_glo.lifo = 1;
	v_glo.cont = 1;
	v_glo.arg = NULL;
	v_glo.head = NULL;
	v_glo.fd = fd;
	v_glo.buffer = NULL;
}

/**
 * free_v_glo - frees the global variables
 *
 * Return: no return
 */

void free_v_glo(void)
{
	free_stack_t(v_glo.head);
	free(v_glo.buffer);
	fclose(v_glo.fd);
}


/**
  * main - entry point of the monty program
  * @argc: argument count
  * @argv: argument array
  * Return: 0 on success
  */

int main(int argc, char *argv[])
{
	FILE *file;
	char *str[2] = {NULL, NULL};
	size_t size = 120;
	ssize_t nline;
	void (*f)(stack_t **stack, unsigned int line_number);
	char *fil = argv[1];

	if (argc != 2)
	{
		perror("USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", fil);
		exit(EXIT_FAILURE);
	}
	start_v_glo(file);

	nline = getline(&v_glo.buffer, &size, v_glo.fd);
	while (nline != -1)
	{
		str[0] = strtok(v_glo.buffer, " \t\n");
		f = get_opcodes(str[0]);
		if (!f)
		{
			fprintf(stderr, "L%u: ", v_glo.cont);
			fprintf(stderr, "unknown instruction %s\n", str[0]);
			free_v_glo();
			exit(EXIT_FAILURE);
		}
		v_glo.arg = strtok(NULL, " \t\n");
		f(&v_glo.head, v_glo.cont);
		nline = getline(&v_glo.buffer, &size, v_glo.fd);
		v_glo.cont++;
	}
	free_v_glo();
	return (EXIT_SUCCESS);
}
