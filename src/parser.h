#ifndef PARSER_H
#define PARSER_H

/*
 * $Id: parser.h,v 1.3 2005/09/04 20:12:06 erik Exp $
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
struct op_s *parsei(int fd);

#endif
