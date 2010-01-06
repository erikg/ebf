/******************************************************************************
 * Copyright (C) 2005-2010 Erik Greenwald. All rights reserved.		      *
 * 									      *
 * Redistribution and use in source and binary forms, with or without	      *
 * modification, are permitted provided that the following conditions	      *
 * are met:								      *
 * 1. Redistributions of source code must retain the above copyright	      *
 *    notice, this list of conditions and the following disclaimer.	      *
 * 2. Redistributions in binary form must reproduce the above copyright	      *
 *    notice, this list of conditions and the following disclaimer in the     *
 *    documentation and/or other materials provided with the distribution.    *
 * 									      *
 * THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND	      *
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE      *
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE *
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE	      *
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL *
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS    *
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)      *
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT *
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY  *
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF     *
 * SUCH DAMAGE.								      *
 *****************************************************************************/

/*
 * $Id: bf2as.c,v 1.17 2010/01/06 01:06:51 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>

#include "lex.h"
#include "parser.h"
#include "optimizer.h"

static const char *head = "\
	.text\n\
	.globl _start\n\
_start:\n\
	movl $heap,%%eax\n";


#ifdef __linux__    /* EXTRA special. */
static const char *tail = "\
	movl  $1, %%eax\n\
	movl $0, %%ebx\n\
	int $0x80\n\
	leave\n\
	ret\n\n\
.data\n\
	.local heap\n\
	.comm heap,30000,32\n";

#else
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

#endif

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
			printf("	movl	0, %%eax\t\t# set to zero\n");
		/*
			printf("	xor %%eax,%%eax\n");
		    */
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
