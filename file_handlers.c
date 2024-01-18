#include "monty.h"

/**
 * open_file - opens a file
 * @file_name: file name
 * Return: void
 */
void open_file(char *file_name)
{
	FILE *fp = fopen(file_name, "r");

	if (!file_name || !fp)
		handle_error(2, file_name);

	read_file(fp);
	fclose(fp);
}

/**
 * read_file - reads a file
 * @fp: file pointer
 * Return: void
 */
void read_file(FILE *fp)
{
	int line, content = 0;
	char *buffer = NULL;
	size_t len = 0;

	for (line = 1; getline(&buffer, &len, fp) != -1; line++)
		content = parse_ln(buffer, line, content);

	free(buffer);
}

/**
 * parse_ln - parses each line
 * @line: line from the file
 * @line_number: line number
 * @format: if 0, nodes will be entered as a stack,
 * if 1, nodes will be entered as a queue
 * Return: 0 if stack, 1 if queue
 */
int parse_ln(char *line, int line_number, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (!line)
		handle_error(4);

	opcode = strtok(line, delim);
	if (!opcode)
		return (format);

	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	choose_func(opcode, value, line_number, format);
	return (format);
}
