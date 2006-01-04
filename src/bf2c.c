
/*
 * $Id: bf2c.c,v 1.4 2006/01/04 17:37:46 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	case INC:
	    CPRINT("++*ptr;","*ptr=*ptr+%d;")
	    break;
	case DEC:
	    CPRINT("--*ptr;","*ptr=*ptr-%d;")
	    break;
	case NEXT:
	    CPRINT("++ptr;","ptr=ptr+%d;")
	    break;
	case PREV:
	    CPRINT("--ptr;","ptr=ptr-%d;")
#undef CPRINT
	    break;
	case PUT:
	    fprintf (out, "putchar(*ptr);");
	    break;
	case GET:
	    fprintf (out, "*ptr = getchar();");
	    break;
	case LOOP_START:
	    fprintf (out, "while(*ptr){");
	    compile_sub (prog->loop, out);
	    fprintf (out, "}");
	    break;
	default:
	    fprintf (stderr, "Unknown symbol in compiled program: %c (0x%X)\n",
		prog->opcode);
	    return -1;
	}
	prog = prog->next;
    }
    return 0;
}

int
compile (char *src, char *dst)
{
    FILE *out;
    struct op_s *prog;

    if ((prog = parse (src)) == NULL)
    {
	printf ("bah, couldn't read %s\n", src);
	return EXIT_FAILURE;
    }
    out = fopen (dst, "w");

    if (out == NULL)
	return printf ("Ack, couldn't open %s for output\n", dst), 1;

    prog = optimize (prog);

    /*
     * dump the front matter 
     */
    fprintf (out,
	"#include <stdio.h>\n\n#define HEAPSIZE 30000\n\nint main(int argc, char **argv) {\n\tchar buf[HEAPSIZE], *ptr = buf;\n\tmemset(buf, 0, HEAPSIZE);\n\n");

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

    while ((c = getopt (argc, argv, "o:vh")) >= 0)
    {
	switch (c)
	{
	case 'o':
	    buf = strdup (optarg);
	    break;
	case 'v':
	    printf
		("%s (bf2c) version $Version$ ($Header: /mnt/fenris/usr/cvs/devel/brainfuck/src/bf2c.c,v 1.4 2006/01/04 17:37:46 erik Exp $)\n",
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
     */
    if (buf == NULL)
    {
	char *ptr;

	buf = strdup (*argv);
	ptr = &buf[strlen (buf)];
	while (ptr > buf && *(ptr - 1) != '.')
	    --ptr;
	*ptr++ = 'c';
	*ptr = '\0';
    }
    return compile (*argv, buf);
}
