#ifndef EVAL_H
#define EVAL_H

/*
 * $Id: eval.h,v 1.2 2005/09/03 17:20:19 erik Exp $
 */

#include "parser.h"

/* interpreted execution of a program */
int eval(struct op_s *program);

#endif
