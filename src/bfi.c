/*
 * $Id: bfi.c,v 1.7 2006/01/04 17:44:00 erik Exp $
 */

#include <stdio.h>

#include "lex.h"
#include "optimizer.h"
#include "parser.h"

#define HEAPSIZE 30000
#define PANIC(x, args...) { printf(x,##args); exit(-1); }

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

int
main(int argc, char **argv) {
    struct op_s *prog;

    /* ensure a valid program filename */
    if(argc<2 || (prog = parse (argv[1])) == NULL) {
	printf("Usage\n\t%s <program.bf>\n", *argv);
	return -1;
    }

    eval(optimize(prog));
    return 0;
}
