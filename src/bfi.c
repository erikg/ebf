/*
 * $Id: bfi.c,v 1.4 2005/09/04 20:12:06 erik Exp $
 */

#include <stdio.h>

#include "eval.h"
#include "parser.h"

#define HEAPSIZE 30000
#define PANIC(x, args...) { printf(x,##args); exit(-1); }

char heap[HEAPSIZE], *ptr, *program;

int
main(int argc, char **argv) {
    struct op_s *prog;

    /* ensure a valid program filename */
    if(argc<2 || (prog = parse (argv[1])) == NULL) {
	printf("Usage\n\t%s <program.bf>\n", *argv);
	return -1;
    }

    eval(prog);
    return 0;
}
