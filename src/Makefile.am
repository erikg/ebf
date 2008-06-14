# $Id: Makefile.am,v 1.8 2008/06/14 13:22:28 erik Exp $

CORE=lex.c parser.c optimizer.c

bin_PROGRAMS=bf2c bfi bfc bf2as bfsc

bf2c_SOURCES=bf2c.c $(CORE)
bfi_SOURCES=bfi.c $(CORE)
bfc_SOURCES=bfc.c $(CORE)
bf2as_SOURCES=bf2as.c $(CORE)
bfsc_SOURCES=bfsc.c $(CORE)

noinst_HEADERS=lex.h parser.h optimizer.h

test: bfi
	(cd ../examples && make tests)
