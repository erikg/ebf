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
 * $Id: bfi.c,v 1.11 2010/01/06 01:06:52 erik Exp $
 */

#include <stdio.h>

#include "lex.h"
#include "optimizer.h"
#include "parser.h"

#define HEAPSIZE 30000

static char heap[HEAPSIZE], *ptr=heap;

int
eval(struct op_s *prog) {
    while( prog ) {
	switch(prog->opcode) {
#define EVAL(op,ex) case op: ex; break;
	    EVAL(ZERO,		*ptr = 0		)
	    EVAL(INC,		*ptr = *ptr + prog->val	)   /* ++*ptr */
	    EVAL(DEC,		*ptr = *ptr - prog->val	)   /* --*ptr */
	    EVAL(NEXT,		ptr += prog->val	)   /* ++ptr */
	    EVAL(PREV,		ptr -= prog->val	)   /* --ptr */
	    EVAL(PUT,		putchar(*ptr)		)
	    EVAL(GET,		*ptr = getchar()	)
	    EVAL(LOOP_START,	while(*ptr)eval(prog->loop))
#undef EVAL
	    default: printf("Unknown symbol in compiled program: %c (0x%X)\n", prog->opcode, prog->opcode); return -1;
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
