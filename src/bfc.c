/*
 * $Id: bfc.c,v 1.1 2005/09/04 20:16:09 erik Exp $
 */

#include <stdio.h>

#include "parser.h"

int
main(int argc, char **argv) {
    struct op_s *prog;

    /* ensure a valid program filename */
    if(argc<2 || (prog = parse (argv[1])) == NULL) {
	printf("Usage\n\t%s <program.bf>\n", *argv);
	return -1;
    }

    return 0;
}
