# $Id: Makefile.am,v 1.13 2008/06/12 20:32:49 erik Exp $

extra_DIST=HELLOBF.BF cat.bf hi.bf hilong.bf lame.bf mandelbrot.b random.b wonk.bf

mandelbrot-c: mandelbrot.b
	$(top_builddir)/src/bf2c $(srcdir)/mandelbrot.b
	gcc -O1 -o mandelbrot-c mandelbrot.c

test-mandelbrot-c: mandelbrot-c
	@echo -n "Testing $@	"
	@/usr/bin/time ./mandelbrot-c > mandelbrot.out
	@if [ ! "`md5 mandelbrot.out`" = "MD5 (mandelbrot.out) = 5024283fa65866ddd347b877798e84d8" ] ; then echo 'bf2c failure!' ; false ; else echo "OK" ; fi
	@rm mandelbrot.c mandelbrot-c 

mandelbrot-as: mandelbrot.b
	@$(top_builddir)/src/bf2as $(srcdir)/mandelbrot.b > mandelbrot-as.s
	@as -o mandelbrot-as.o mandelbrot-as.s
	@ld -o mandelbrot-as mandelbrot-as.o

test-mandelbrot-as: mandelbrot-as
	@echo -n "Testing $@	"
	@/usr/bin/time ./mandelbrot-as > mandelbrot.out
	@if [ ! "`md5 mandelbrot.out`" = "MD5 (mandelbrot.out) = 5024283fa65866ddd347b877798e84d8" ] ; then echo 'bf2as failure!' ; false ; else echo "OK" ; fi
	@rm mandelbrot-as mandelbrot-as.o mandelbrot-as.s 

test-mandelbrot-bfi:
	@echo -n "Testing $@	"
	@/usr/bin/time $(top_builddir)/src/bfi $(srcdir)/mandelbrot.b > mandelbrot.out
	@if [ ! "`md5 mandelbrot.out`" = "MD5 (mandelbrot.out) = 5024283fa65866ddd347b877798e84d8" ] ; then echo 'bfi failure!' ; false ; else echo "OK" ; fi

test-mandelbrot: mandelbrot-c mandelbrot-as test-mandelbrot-c test-mandelbrot-as test-mandelbrot-bfi 

test-hi1:
	@echo -n "Testing $@	"
	@if [ "`$(top_builddir)/src/bfi $(srcdir)/hi.bf`" != 'Hello World!' ] ; then echo 'Grar, failure!' ; false ; else echo "OK" ; fi

test-hi-as:
	@echo -n "Testing ASM:	"
	@$(top_builddir)/src/bf2as $(srcdir)/hi.bf > hi-as.s
	@as -o hi-as.o hi-as.s
	@ld -o hi-as hi-as.o
	@./hi-as
	@rm hi-as hi-as.o hi-as.s 

test-hi-c:
	@echo -n "Testing C:	"
	@$(top_builddir)/src/bf2c $(srcdir)/hi.bf
	@mv hi.c hi-c.c
	@cc -o hi-c.o hi-c.c
	@ld -o hi-c hi-c.o
	@./hi-c
	@rm hi-c hi-c.o hi-c.c

test-hi2:
	@echo -n "Testing $@	"
	@if [ "`$(top_builddir)/src/bfi $(srcdir)/hilong.bf`" != 'Hello World!' ] ; then echo 'Grar, failure!' ; false ; else echo "OK" ; fi

tests: test-hi1 test-hi2 test-hi-c test-hi-as test-mandelbrot

clean:
	rm -f mandelbrot-as mandelbrot-as.o mandelbrot-as.s mandelbrot.c mandelbrot-c mandelbrot.out
