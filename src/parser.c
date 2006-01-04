
/*
 * $Id: parser.c,v 1.5 2006/01/04 15:17:44 erik Exp $
 */

#include <stdio.h>

#include "parser.h"
#include "lex.h"

struct op_s *
parsei (int fd)
{
    int op;
    struct op_s *prog = NULL, *ptr = NULL, *cell;

    while (op = lex_next (fd))
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

int
prog_length (struct op_s *prog)
{
    return prog == NULL ? 0 : 1 + prog_length (prog->next);
}

void
prog_print (struct op_s *prog)
{
    while (prog)
    {
	putchar (prog->opcode);
	if (prog->opcode == LOOP_START)
	{
	    prog_print (prog->loop);
	    putchar (']');
	}
	prog = prog->next;
    }
    return;
}
