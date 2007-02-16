#ifndef LEX_H
#define LEX_H

/*
 * $Id: lex.h,v 1.3 2007/02/16 17:35:33 erik Exp $
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
