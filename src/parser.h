#ifndef PARSER_H
#define PARSER_H

/*
 * $Id: parser.h,v 1.4 2006/01/03 22:37:50 erik Exp $
 */

struct op_s {
	char opcode;
	int val;
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

int prog_length(struct op_s *prog);

#endif
