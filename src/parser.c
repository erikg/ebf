
/*
 * $Id: parser.c,v 1.7 2007/02/16 15:33:44 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "lex.h"

struct op_s *
parsei (int fd)
{
    int op;
    struct op_s *prog = NULL, *ptr = NULL, *cell;

    while ((op = lex_next (fd)) != 0)
    {
	if (op == LOOP_END)
	    return prog;

	cell = (struct op_s *)malloc (sizeof (struct op_s));

	if (prog == NULL)
	    prog = cell;
	else
	    ptr->next = cell;
	ptr = cell;

	cell->opcode = op;
	cell->val = 1;
	cell->next = NULL;
	cell->loop = (op == LOOP_START) ? parsei (fd) : NULL;
    }
    return prog;
}

struct op_s *
parse (char *filename)
{
    int fd;

    return (fd = lex_open (filename)) < 0 ? NULL : parsei (fd);
}

void
prog_print (struct op_s *prog)
{
    while (prog)
    {
	int i = prog->val;

	while(i--)
	    putchar (prog->opcode);
	if (prog->opcode == LOOP_START)
	{
	    prog_print (prog->loop);
	    printf ("]");
	}
	prog = prog->next;
    }
    return;
}
