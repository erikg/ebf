/*
 * $Id: bfi.c,v 1.2 2005/09/03 17:20:19 erik Exp $
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

    printf("\n");

    eval(prog);
    printf("\n");
    return 0;
}
