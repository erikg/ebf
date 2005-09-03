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
