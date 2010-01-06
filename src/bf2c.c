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
 * $Id: bf2c.c,v 1.14 2010/01/06 01:06:51 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>

#include "lex.h"
#include "parser.h"
#include "optimizer.h"

int
compile_sub (struct op_s *prog, FILE * out)
{
    while (prog)
    {
	switch (prog->opcode)
	{
#define CPRINT(u,m) { if (prog->val == 1) fprintf (out, u); else fprintf (out, m, prog->val); }
	case INC: CPRINT("++*ptr;","*ptr= *ptr+%d;") break;
	case DEC: CPRINT("--*ptr;","*ptr= *ptr-%d;") break;
	case NEXT: CPRINT("++ptr;","ptr=ptr+%d;") break;
	case PREV: CPRINT("--ptr;","ptr=ptr-%d;") break;
#undef CPRINT
	case ZERO: fprintf(out, "*ptr = 0;"); break;
	case PUT: fprintf (out, "write(STDOUT_FILENO,ptr,1);"); break;
	case GET: fprintf (out, "read(STDIN_FILENO,ptr,1);"); break;
	case LOOP_START:
	    fprintf (out, "while(*ptr){");
	    compile_sub (prog->loop, out);
	    fprintf (out, "}");
	    break;
	default:
	    fprintf (stderr, "Unknown symbol in compiled program: %c (0x%X)\n",
		prog->opcode, prog->opcode);
	    return -1;
	}
	prog = prog->next;
    }
    return 0;
}

int
compile (FILE *src, FILE *out)
{
    struct op_s *prog;

    if ((prog = optimize(parsei(fileno(src)))) == NULL)
    {
	printf ("bah, couldn't read source file\n", src);
	return EXIT_FAILURE;
    }

    /*
     * dump the front matter 
     */
    fprintf (out,
	"#include <stdio.h>\n#include <string.h>\n#include <unistd.h>\n\n#define HEAPSIZE 30000\n\nint main(int argc, char **argv) {\n\tchar buf[HEAPSIZE], *ptr = buf;\n\tmemset(buf, 0, HEAPSIZE);\n\n");

    /*
     * then the body, we'll let the c compiler worry about optimizing 
     */
    compile_sub (prog, out);

    /*
     * and the back matter 
     */
    fprintf (out, "\n\treturn 0;\n}\n");
    fclose (out);
    return 0;
}

int
main (int argc, char **argv)
{
    int c;
    char *buf = NULL;
    char src[BUFSIZ];
    FILE *in, *out;

    while ((c = getopt (argc, argv, "o:vh")) >= 0)
    {
	switch (c)
	{
	case 'o':
	    buf = strdup (optarg);
	    break;
	case 'v':
	    printf
		("%s (bf2c) version $Version$ ($Header: /mnt/fenris/usr/cvs/devel/brainfuck/src/bf2c.c,v 1.14 2010/01/06 01:06:51 erik Exp $)\n",
		*argv);
	    return 0;
	case 'h':
	    printf ("Usage:\n\t%s [-o <output.c>] [-v|-h] <prog.bf>\n", *argv);
	    return 0;
	default:
	    printf ("Something or rather: %c\n", c);
	}
    }

    argc -= optind;
    argv += optind;

    /*
     * transmogrify the .bf or .b or whatever name to .c 
     * TODO: basename it
     */
    if (buf == NULL)
    {
	char *ptr;

	buf = strdup (basename (*argv));
	ptr = &buf[strlen (buf)];
	while (ptr > buf && *(ptr - 1) != '.')
	    --ptr;
	*ptr++ = 'c';
	*ptr = '\0';
    }

    in = fopen (*argv, "r");
    if(in == NULL) {
	printf("Failed to open %s", *argv);
	perror("");
	return -1;
    }

    out = fopen (buf, "w");
    if (out == NULL) {
	printf ("Ack, couldn't open %s for output", buf);
	perror ("");
	return -1;
    }

    return compile (in, out);
}
