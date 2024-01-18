#include "monty.h"

/**
 * choose_func - choose the appropriate function according to
 * the corresponding opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @format: if 0, nodes will be entered as a stack,
 * if 1, nodes will be entered as a queue
 * @ln: line number
 * Return: void
 */
void choose_func(char *opcode, char *value, int ln, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", add_to_stack},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			call_fun(func_list[i].f, opcode, value, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		handle_error(3, ln, opcode);
}

/**
 * call_fun - Calls the appropriate function
 * @func: pointer to the function that should be called
 * @op: opcode
 * @val: argument of opcode
 * @ln: line numeber
 * @format: if 0, nodes will be entered as a stack,
 * if 1, nodes will be entered as a queue
 */
void call_fun(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (!val)
			handle_error(5, ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				handle_error(5, ln);
		}
		node = create_node(atoi(val) * flag);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add_to_queue(&node, ln);
	}
	else
		func(&head, ln);
}
