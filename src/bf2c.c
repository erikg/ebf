#include <stdio.h>
#include <unistd.h>

int
compile(char *src, char *dst) {
    FILE *in, *out;
    char buf[BUFSIZ];
    int op;

    in = fopen(src, "r");
    out = fopen(dst, "w");

    if(in==NULL || out==NULL)
	return printf("Ack, couldn't open one of the files... \n"), -1;

    /* dump the fore matter */
    fprintf(out, "#include <stdio.h>\n\n#define HEAPSIZE 30000\n\nint main(int argc, char **argv) {\n\tchar buf[HEAPSIZE], *ptr = buf;\n\tmemset(buf, 0, HEAPSIZE);\n\n");

    /* then the body, we'll let the c compiler worry about optimizing */
    while((op = fgetc(in)) != EOF)
	switch(op) {
	    case '>': fprintf(out, "++ptr;\n"); break;
	    case '<': fprintf(out, "--ptr;\n"); break;
	    case '+': fprintf(out, "++*ptr;\n"); break;
	    case '-': fprintf(out, "--*ptr;\n"); break;
	    case '.': fprintf(out, "putchar(*ptr);\n"); break;
	    case ',': fprintf(out, "*ptr = getchar();\n"); break;
	    case '[': fprintf(out, "while(*ptr) {\n"); break;
	    case ']': fprintf(out, "}\n"); break;
	}

    fclose(in);
    /* and the back matter */
    fprintf(out, "\n\treturn 0;\n}\n");
    fclose(out);
    return 0;
}

int main(int argc, char **argv) {
    int c;
    char *buf = NULL;

    while((c=getopt(argc, argv, "o:vh"))>=0){
	switch(c) {
	    case 'o':
		buf = strdup(optarg);
		break;
	    case 'v':
		printf("%s (bf2c) version $Version$ ($Header: /mnt/fenris/usr/cvs/devel/brainfuck/src/bf2c.c,v 1.1 2005/09/03 16:52:05 erik Exp $)\n", *argv);
		return 0;
	    case 'h':
		printf("Usage:\n\t%s [-o <output.c>] [-v|-h] <prog.bf>\n", *argv);
		return 0;
	    default:
		printf("Something or rather: %c\n", c);
	}
    }

    argc-=optind;
    argv+=optind;

    /* transmogrify the .bf or .b or whatever name to .c */
    if(buf==NULL){
	char *ptr;
	buf = strdup(*argv);
	ptr = &buf[strlen(buf)];
	while(ptr>buf && *(ptr-1) != '.')
	    --ptr;
	*ptr++ = 'c';
	*ptr = '\0';
    }

    return compile(*argv, buf);
}
