/*
 * $Id: bfi.c,v 1.6 2006/01/04 17:38:22 erik Exp $
 */

#include <stdio.h>

#include "eval.h"
#include "parser.h"
#include "optimizer.h"

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

    eval(optimize(prog));
    return 0;
}
