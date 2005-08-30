#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>

#define HEAPSIZE 30000

#define PANIC(x, args...) { printf(x,##args); exit(-1); }

char *heap, *ptr;
int i = 0, fd;

void eval(char op) {
    ++i;
    switch(op) {
	case '>': if((ptr-heap)<HEAPSIZE) ptr++; else PANIC("Past heap end at opcode: %d\n", i); break;
	case '<': if(ptr>heap) ptr--; else PANIC("Before heap start at opcode: %d\n", i); break;
	case '+': ++*ptr; break;
	case '-': --*ptr; break;
	case '.': putchar(*ptr); break;
	case ',': *ptr = getchar(); break;
	case '[': while(*ptr){ char op; read(fd, 
	case ']': PANIC("NOOP! ]"); break;
	default: break;
    }
}

int
main(int argc, char **argv) {
    char op;

    printf("%s\n", argv[1]);
    if(argc<1 || (fd = open(argv[1], O_RDONLY)) == -1)
	PANIC("usage:\n\t%s <program.bf>\n", *argv);

    /* set up the heap */
    ptr = heap = (char *)malloc(HEAPSIZE);
    memset(heap, 0, HEAPSIZE);

    while(read(fd, &op, 1)) {
	eval(op);
    }

    return 0;
}
