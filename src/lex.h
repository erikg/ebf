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
#ifndef LEX_H
#define LEX_H

/*
 * $Id: lex.h,v 1.4 2008/06/13 23:23:18 erik Exp $
 */

/* the brainfuck lexicon */
#define INC		'+'
#define DEC		'-'
#define NEXT		'>'
#define PREV		'<'
#define GET		','
#define PUT		'.'
#define LOOP_START	'['
#define LOOP_END	']'

#define ZERO		'0'

/* just an open, will try searching for .b and .bf */
int lex_open(char *file);

/* get the next legal brainfuck token */
int lex_next(int fd);

/* close... */
#define LEX_CLOSE close

#endif
