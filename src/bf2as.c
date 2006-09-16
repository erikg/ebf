
/*
 * $Id: bf2as.c,v 1.5 2006/09/16 00:16:40 erik Exp $
 */

#include <stdio.h>

#include "lex.h"
#include "parser.h"

static const char *head = "\
	.text\n\
	.global _start\n\
kernel:\n\
	int $0x80\n\
	ret\n\
_start:\n\
	movl $heap,%%eax\n";
static const char *tail = "\
	pushl $0\n\
	movl  $1, %%eax\n\
	call  kernel\n\
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
#define OP(o,c) case o: printf(c); break
		OP(INC,  "	incl (%%eax)	# +\n");
		OP(DEC,  "	decl (%%eax)	# -\n");
		OP(NEXT, "	incl  %%eax	# >\n");
		OP(PREV, "	decl  %%eax	# <\n");
		OP(GET,  "	*** GET\t\t# ,\n");
#undef OP
		case PUT:
			printf("	pushl %%eax\n");
			printf("	pushl $1\n");
			printf("	pushl %%eax\n");
			printf("	pushl $1\n");
			printf("	movl  $4, %%eax\n");
			printf("	call  kernel\n");
			printf("	addl  $12, %%esp\n");
			printf("	popl  %%eax\n");
			break;
		case LOOP_START:
			labelval = labelcount;
			++labelcount;
			sprintf(label, "B%04d", labelval);
			sprintf(endlabel, "E%04d", labelval);
			printf("%s:\t\t\t# [\n", label);
			printf("	cmpb $0, (%%eax)\n");
			printf("	jz %s\n", endlabel);
			x86(prog->loop);
			printf("	jmp %s	# ]\n", label);
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
	x86(prog);
	printf(tail);
	return 0;
}
