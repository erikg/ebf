#include <stdio.h>

#include "parser.h"
#include "lex.h"

struct op_s *
fromp (int fd)
{
    int op;
    struct op_s *prog = NULL, *ptr = NULL;

    while (op = lex_next (fd))
    {
	struct op_s *cell;

	if(op==0 || op==LOOP_END)
	    return prog;
	
	cell = (struct op_s *)malloc (sizeof (struct op_s));

	if (prog == NULL)
	    prog = cell;
	else
	    ptr->next = cell;
	ptr = cell;

	cell->opcode = op;
	cell->next = NULL;
	cell->loop = (op == LOOP_START) ? fromp (fd) : NULL;
    }
    return prog;
}

struct op_s *
parse (char *filename)
{
    int fd = lex_open (filename);

    if (fd < 0)
	return NULL;

    return fromp (fd);
}
