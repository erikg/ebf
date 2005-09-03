#ifndef LEX_H
#define LEX_H

/*
 * $Id: lex.h,v 1.2 2005/09/03 17:20:19 erik Exp $
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

/* just an open, will try searching for .b and .bf */
int lex_open(char *file);

/* get the next legal brainfuck token */
int lex_next(int fd);

/* close... */
#define LEX_CLOSE close

#endif
