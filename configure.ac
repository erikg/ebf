dnl $Id: configure.ac,v 1.2 2008/06/12 20:34:31 erik Exp $

AC_INIT
AC_CONFIG_SRCDIR([src/bfi.c])
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE(ebf, 1.0) # Erik's BrainFuck

AC_PROG_CC
AC_PROG_INSTALL

AC_CHECK_HEADERS(fcntl.h sys/types.h sys/uio.h unistd.h)

AC_CONFIG_FILES(Makefile src/Makefile examples/Makefile)
AC_OUTPUT
