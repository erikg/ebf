#ifndef PARSER_H
#define PARSER_H

/*
 * $Id: parser.h,v 1.6 2006/09/22 14:02:18 erik Exp $
 */

struct op_s {
	char opcode;
	int val;	    /* extra info for optimizations... repetition count */
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
void prog_print(struct op_s *prog);

#endif
