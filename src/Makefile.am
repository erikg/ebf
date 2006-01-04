# $Id: Makefile.am,v 1.6 2006/01/04 17:37:54 erik Exp $

CORE=lex.c parser.c optimizer.c

bin_PROGRAMS=bf2c bfi bfc bf2as

bf2c_SOURCES=bf2c.c $(CORE)
bfi_SOURCES=bfi.c eval.c $(CORE)
bfc_SOURCES=bfc.c $(CORE)
bf2as_SOURCES=bf2as.c $(CORE)

noinst_HEADERS=lex.h parser.h eval.h optimizer.h

test: bfi
	(cd ../examples && make tests)
