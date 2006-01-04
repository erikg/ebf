# $Id: Makefile.am,v 1.5 2006/01/04 15:17:57 erik Exp $

bin_PROGRAMS=bf2c bfi bfc bf2as

bf2c_SOURCES=bf2c.c
bfi_SOURCES=bfi.c lex.c parser.c optimizer.c eval.c
bfc_SOURCES=bfc.c lex.c parser.c
bf2as_SOURCES=bf2as.c lex.c parser.c

noinst_HEADERS=lex.h parser.h eval.h optimizer.h

test: bfi
	(cd ../examples && make tests)
