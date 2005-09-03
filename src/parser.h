#ifndef PARSER_H
#define PARSER_H

/*
 * $Id: parser.h,v 1.2 2005/09/03 17:20:19 erik Exp $
 */

struct op_s {
	char opcode;
	struct op_s *loop;
	struct op_s *next;
};

/** 
 * parse the grammar of the brainfuck program.
 * @param filename the brainfuck program to load.
 * @return the program structure.
 */
struct op_s *parse(char *filename);

#endif
