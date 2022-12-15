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
 * free_vglo - frees the global variables
 *
 * Return: no return
 */

void free_v_glo(void)
{
	free_dlistint(v_glo.head);
	free(v_glo.buffer);
	fclose(v_glo.fd);
}

/**
  * split - splits strings
  * @line: string to be splitted
  *
  * Return: splitted strings
  */

char *split(char *line)
{
	char *delim = " \t\n", *token, *arr[2];
	int i = 0;

	token = strtok(line, delim);
	while (token != NULL)
	{
		arr[i++] = token;
		token = strtok(NULL, delim);
	}
	return (arr);
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
	char *str;
	size_t *size = 200;
	ssize_t nline;
	void (*f)(stack_t **stack, unsigned int line_number);

	if (argc != 2)
	{
		perror("USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", v_glo.fd);
		exit(EXIT_FAILURE);
	}
	start_v_glo(file);

	nline = getline(&v_glo.buffer, size, v_glo.fd);
	while (nline != -1)
	{
		str = split(v_glo.buffer);
		if (str[0] && str[1] != '#')
		{
			f = get_opcode(str[0]);
			if (!f)
			{
				fprintf(stderr, "L%u: ", v_glo.cont);
				fprintf(stderr, "unknown instruction %s\n", str[0]);
				free_v_glo();
				exit(EXIT_FAILURE);
			}
			v_glo.arg = str[1];
			f(&v_glo.head, vglo.cont);
		}
		nline = getline(&v_glo.buffer, &size, v_glo.fd);
		v_glo.cont++;
	}
	free_v_glo();
	return (EXIT_SUCCESS);
}
