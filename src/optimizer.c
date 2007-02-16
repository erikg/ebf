/*
 * $Id: optimizer.c,v 1.10 2007/02/16 17:37:42 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>

#include "lex.h"
#include "optimizer.h"

static struct op_s *
compact (struct op_s *prog)
{
    struct op_s *ret = prog;

    while (prog)
    {
	if (prog->opcode == LOOP_START)
	    prog->loop = compact (prog->loop);
	else if((prog->opcode == INC || prog->opcode == DEC || prog->opcode == NEXT || prog->opcode == PREV))
	    while(prog->next && prog->opcode == prog->next->opcode) {
		struct op_s *t = prog->next;

		prog->next = t->next;
		prog->val += t->val;
		free(t);
	    }
	prog = prog->next;
    }
    return ret;
}

static struct op_s *
deduce_zeros(struct op_s *prog){
    struct op_s *t = prog;
    if(prog->opcode == DEC && prog->next==NULL)
	prog->opcode = ZERO;
    while(prog) {
	if(prog->opcode == LOOP_START)
	    prog->loop = deduce_zeros(prog->loop);
	prog = prog->next;
    }
    return t;
}

struct op_s *
optimize (struct op_s *prog)
{
    return compact (prog);
}
