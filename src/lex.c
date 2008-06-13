/******************************************************************************
 * Copyright (C) 2005-2008 Erik Greenwald. All rights reserved.		      *
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
 * $Id: lex.c,v 1.3 2008/06/13 23:23:18 erik Exp $
 */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

#include "lex.h"

static int
istoken (char c)
{
    return c == INC || c == DEC || c == NEXT || c == PREV || c == GET
	|| c == PUT || c == LOOP_START || c == LOOP_END;
}

int
lex_open (char *filename)
{
    return open (filename, O_RDONLY);
}

int
lex_next (int fd)
{
    char c;

    do
	if(read (fd, &c, sizeof (char))==0)
	    return 0;
    while (!(istoken (c)));
    return c;
}
