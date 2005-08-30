#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int c;

    while((c=getopt(argc, argv, "o:vh"))!=0){
	switch(c) {
	    case 'o':
		break;
	    case 'v':
		printf("%s (bf2c) version $Version$ ($Header: /mnt/fenris/usr/cvs/devel/brainfuck/Attic/bf2c.c,v 1.2 2005/08/30 02:42:22 erik Exp $)\n", *argv);
		break;
	    case 'h':
		break;

	}
    }
}
