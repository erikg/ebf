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
 * $Id: parser.c,v 1.9 2010/01/06 01:06:52 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "lex.h"

struct op_s *
parsei (int fd)
{
    int op;
    struct op_s *prog = NULL, *ptr = NULL, *cell;

    while ((op = lex_next (fd)) != 0)
    {
	if (op == LOOP_END)
	    return prog;

	cell = (struct op_s *)malloc (sizeof (struct op_s));

	if (prog == NULL)
	    prog = cell;
	else
	    ptr->next = cell;
	ptr = cell;

	cell->opcode = op;
	cell->val = 1;
	cell->next = NULL;
	cell->loop = (op == LOOP_START) ? parsei (fd) : NULL;
    }
    return prog;
}

struct op_s *
parse (char *filename)
{
    int fd;

    return (fd = lex_open (filename)) < 0 ? NULL : parsei (fd);
}

void
prog_print (struct op_s *prog)
{
    while (prog)
    {
	int i = prog->val;

	while(i--)
	    putchar (prog->opcode);
	if (prog->opcode == LOOP_START)
	{
	    prog_print (prog->loop);
	    printf ("]");
	}
	prog = prog->next;
    }
    return;
}
