#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int c;

    while((c=getopt(argc, argv, "o:vh"))!=0){
	switch(c) {
	    case 'o':
		break;
	    case 'v':
		printf("%s (bf2c) version $version$ ($header$)\n", *argv);
		break;
	    case 'h':
		break;

	}
    }
}
