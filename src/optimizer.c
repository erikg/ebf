#include <stdio.h>

#include "lex.h"
#include "optimizer.h"

static struct op_s *
compact (struct op_s *prog)
{
    if (prog && prog->next)
	switch (prog->opcode)
	{
	    case INC:
	    case DEC:
	    case NEXT:
	    case PREV:
	    if (prog->opcode == prog->next->opcode)
	    {
		struct op_s *tmp = prog->next;

		prog->val += tmp->val;
		prog->next = tmp->next;
		free (tmp);
		return compact (prog), prog;
	    } else
		return compact (prog->next), prog;
	    break;
	default:
	    return compact (prog->next), prog;
	}
    return NULL;
}

struct op_s *
optimize (struct op_s *prog)
{
    return compact (prog);
}
