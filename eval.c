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
	    EVAL(INC,		++*ptr		)
	    EVAL(DEC,		--*ptr		)
	    EVAL(NEXT,		++ptr		)
	    EVAL(PREV,		--ptr		)
	    EVAL(PUT,		putchar(*ptr)	)
	    EVAL(GET,		*ptr = getchar())
	    EVAL(LOOP_START,	while(*ptr)eval(prog->loop))
#undef EVAL
	    default: printf("Unknown symbol in compiled program: %c (0x%X)\n", prog->opcode); return -1;
	}
	prog = prog->next;
    }
    return 0;
}
