#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>

#define HEAPSIZE 30000

#define PANIC(x, args...) { printf(x,##args); exit(-1); }

char heap[HEAPSIZE], *ptr, *program;
int i = 0, proglen;

void eval(char op) {
    switch(op){
    case '+': break;
    case '-': break;
    case '>': break;
    case '<': break;
    case ',': break;
    case '.': break;
    case '[': break;
    case ']': break;
    }
    return;
}

void reduce(char *prog, int pl) {
    char *np = prog;
    int first=1;

    while(pl--) {
    }
}

int
main(int argc, char **argv) {
    struct stat sb;
    int fd;

    /* ensure a valid program filename */
    if(argc!=2 || stat(argv[1], &sb))
    {
	printf("Usage\n\t%s <program.bf>\n", *argv);
	return -1;
    }

    /* read the program into memory */
    proglen = sb.st_size;
    program = (char *)malloc(proglen);
    fd = open(argv[1], O_RDONLY);
    read(fd,program,proglen);
    close(fd);

    reduce(program, proglen);
    
    printf("program: %s\n", program);

    return 0;
}
