/*
 * $Id: eval.c,v 1.4 2006/01/04 15:25:52 erik Exp $
 */

#include <stdio.h>

#include "eval.h"
#include "lex.h"
#include "parser.h"

static char heap[30000], *ptr=heap;

int
eval(struct op_s *prog) {
    while( prog ) {
	switch(prog->opcode) {
#define EVAL(op,ex) case op: ex; break;
	    EVAL(INC,		*ptr = *ptr + prog->val	)   /* ++*ptr */
	    EVAL(DEC,		*ptr = *ptr - prog->val	)   /* --*ptr */
	    EVAL(NEXT,		ptr += prog->val	)   /* ++ptr */
	    EVAL(PREV,		ptr -= prog->val	)   /* --ptr */
	    EVAL(PUT,		putchar(*ptr)		)
	    EVAL(GET,		*ptr = getchar()	)
	    EVAL(LOOP_START,	while(*ptr)eval(prog->loop))
#undef EVAL
	    default: printf("Unknown symbol in compiled program: %c (0x%X)\n", prog->opcode); return -1;
	}
	prog = prog->next;
    }
    return 0;
}
