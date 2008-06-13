dnl $Id: configure.ac,v 1.4 2008/06/13 23:23:18 erik Exp $

AC_INIT
AC_CONFIG_SRCDIR([src/bfi.c])
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE(ebf, 0.1) # Erik's BrainFuck

AC_PROG_CC
AC_PROG_INSTALL

AC_CHECK_HEADERS(fcntl.h libgen.h sys/types.h sys/uio.h unistd.h)

AC_CONFIG_FILES(Makefile src/Makefile examples/Makefile)
AC_OUTPUT
