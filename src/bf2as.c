
/*
 * $Id: bf2as.c,v 1.1 2005/09/05 17:41:22 erik Exp $
 */

#include <stdio.h>

#include "lex.h"
#include "eval.h"
#include "parser.h"

int labelcount = 0;

void 
x86(struct op_s *prog, char *oldlabel, char *label) {
    char newlabel[] = "L0000";

    while(prog) {
	switch(prog->opcode){
#define OP(o,c) case o: printf(c); break
	OP(INC, "	inc (%%al)\t; +\n");
	OP(DEC, "	dec (%%al)\t; -\n");
	OP(NEXT, "	inc %%al\t; >\n");
	OP(PREV, "	dec %%al\t; <\n");
	OP(GET, "	*** GET\t\t; ,\n");
	OP(PUT, "	*** PUT\t\t; .\n");
#undef OP
	case LOOP_START:
	    sprintf(newlabel, "L%04d", labelcount++);
	    printf("%s:\t\t\t; [\n", label);
	    printf("	cmp (%%al), 0\n");
	    printf("	jnz %s\t\n", newlabel);
	    x86(prog->loop, label, newlabel);
	    break;
	default:
	    printf("Unknown opcode: %x \"%c\"\n", prog->opcode, prog->opcode);
	    exit(-1);
	}
	prog = prog->next;
    }
    if(oldlabel){
	printf("	jmp %s\t; ]\n", oldlabel);
	printf("%s:\t\t\t\n", label);
    }
}

int
main(int argc, char **argv) {
    struct op_s *prog;

    /* ensure a valid program filename */
    if(argc<2 || (prog = parse (argv[1])) == NULL) {
	printf("Usage\n\t%s <program.bf>\n", *argv);
	return -1;
    }

    printf(".text\n_start:\n\tmovl $heap,%%eax\n");
    x86(prog, NULL, "ROOT");
    printf("\tleave\n\tret\n\n.data\n\t.local heap\n\t.comm heap,30000,32\n");
    return 0;
}
