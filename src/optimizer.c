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
 * $Id: optimizer.c,v 1.13 2010/01/06 01:06:52 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>

#include "lex.h"
#include "optimizer.h"

static struct op_s *
compact (struct op_s *prog)
{
    struct op_s *ret = prog;

    while (prog)
    {
	if (prog->opcode == LOOP_START)
	    prog->loop = compact (prog->loop);
	else if((prog->opcode == INC || prog->opcode == DEC || prog->opcode == NEXT || prog->opcode == PREV))
	    while(prog->next && prog->opcode == prog->next->opcode) {
		struct op_s *t = prog->next;

		prog->next = t->next;
		prog->val += t->val;
		free(t);
	    }
	prog = prog->next;
    }
    return ret;
}

static struct op_s *
deduce_zeros(struct op_s *prog){
    struct op_s *t = prog;
    if(prog->opcode == DEC && prog->next==NULL)
	prog->opcode = ZERO;
    while(prog) {
	if(prog->opcode == LOOP_START)
	    prog->loop = deduce_zeros(prog->loop);
	prog = prog->next;
    }
    return t;
}

struct op_s *
optimize (struct op_s *prog)
{
    prog = compact(prog);
    prog = deduce_zeros(prog);
    return prog;
}
