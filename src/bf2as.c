
/*
 * $Id: bf2as.c,v 1.12 2007/02/19 18:41:12 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>

#include "lex.h"
#include "parser.h"
#include "optimizer.h"

static const char *head = "\
	.text\n\
	.global _start\n\
_start:\n\
	movl $heap,%%eax\n";
static const char *tail = "\
	pushl $0\n\
	movl  $1, %%eax\n\
	pushl $0\n\
	int $0x80\n\
	leave\n\
	ret\n\n\
.data\n\
	.local heap\n\
	.comm heap,30000,32\n";

int labelcount = 0;

void 
x86(struct op_s *prog) {
	char label[] = "L####", endlabel[] = "L####";
	int labelval = labelcount;

	while(prog) {
		switch(prog->opcode){
#define OP(o, args) case o: printf( args ); break
		OP(GET,  "	*** GET\t\t# ,\n");
#define OPT(op,a,b) case op: if(prog->val==1) a; else b; break
		OPT(DEC,
		    printf("	decl  (%%eax)\t\t# -\n"),
		    printf("	subl  $%d, (%%eax)\t\t# - %d\n",prog->val,prog->val););
		OPT(PREV,
		    printf("	decl  %%eax\t\t# <\n"),
		    printf("	subl  $%d, %%eax\t\t# < %d\n",prog->val,prog->val););
		OPT(NEXT,
		    printf("	incl  %%eax\t\t# >\n"),
		    printf("	addl  $%d, %%eax\t# > %d\n", prog->val, prog->val));
		OPT(INC,
		    printf("	incl  (%%eax)\t\t# +\n"),
		    printf("	addl  $%d,(%%eax)\t\t# + %d\n", prog->val, prog->val));
		case ZERO:
			printf("	xor (%%eax),(%%eax)\n");
			break;
		case PUT:
			printf("			\t# .\n");
			printf("	pushl %%eax\n");
#ifdef __linux__
			/* DOS calling convention, register fill */
			printf("	movl  %%eax, %%ecx\n");
			printf("	movl  $1, %%ebx\n");
			printf("	movl  $1, %%edx\n");
#else
			/* UNIX/C calling convention, stack use */
			printf("	pushl $1\n");
			printf("	pushl %%eax\n");
			printf("	pushl $1\n");
			printf("	pushl %%eax\t#noise\n");
#endif
			printf("	movl  $4, %%eax\n");
			printf("	int $0x80\n\n");
#ifndef __linux__
			printf("	addl  $16, %%esp\n");
#endif
			printf("	popl  %%eax\n\n");
			break;
		case LOOP_START:
			labelval = labelcount;
			++labelcount;
			sprintf(label, "B%04d", labelval);
			sprintf(endlabel, "E%04d", labelval);
			printf("%s:\t\t\t\t# [\n", label);
			printf("	cmpb  $0, (%%eax)\n");
			printf("	jz    %s\n", endlabel);
			x86(prog->loop);
			printf("	jmp   %s	\t# ]\n", label);
			printf("%s:			\n", endlabel);
			break;
		default:
			printf("Unknown opcode: %x \"%c\"\n", prog->opcode, prog->opcode);
			exit(-1);
		}
		prog = prog->next;
	}
	return;
}

int
main(int argc, char **argv) {
	struct op_s *prog;

	/* ensure a valid program filename */
	if(argc<2 || (prog = parse (argv[1])) == NULL) {
	printf("Usage\n	%s <program.bf>\n", *argv);
	return -1;
	}

	printf("#\n# ");
	prog_print(prog);
	printf("#\n#\n#\n\n");
	printf(head);
	x86(optimize(prog));
	printf(tail);
	return 0;
}
