# $Id: Makefile.am,v 1.9 2007/02/17 13:22:28 erik Exp $

extra_DIST=HELLOBF.BF cat.bf hi.bf hilong.bf lame.bf mandelbrot.b random.b wonk.bf

mandelbrot-c: mandelbrot.b
	../src/bf2c mandelbrot.b
	gcc -O1 -o mandelbrot-c mandelbrot.c

test-mandelbrot-c: mandelbrot-c
	@echo -n "Testing $@	"
	@/usr/bin/time ./mandelbrot-c > mandelbrot.out
	@if [ ! "`md5 mandelbrot.out`" = "MD5 (mandelbrot.out) = 5024283fa65866ddd347b877798e84d8" ] ; then echo 'bf2c failure!' ; false ; else echo "OK" ; fi

mandelbrot-as: mandelbrot.b
	../src/bf2as mandelbrot.b > mandelbrot-as.s
	as -o mandelbrot-as.o mandelbrot-as.s
	ld -o mandelbrot-as mandelbrot-as.o

test-mandelbrot-as: mandelbrot-as
	@echo -n "Testing $@	"
	@/usr/bin/time ./mandelbrot-as > mandelbrot.out
	@if [ ! "`md5 mandelbrot.out`" = "MD5 (mandelbrot.out) = 5024283fa65866ddd347b877798e84d8" ] ; then echo 'bf2as failure!' ; false ; else echo "OK" ; fi

test-mandelbrot-bfi:
	@echo -n "Testing $@	"
	@/usr/bin/time ../src/bfi mandelbrot.b > mandelbrot.out
	@if [ ! "`md5 mandelbrot.out`" = "MD5 (mandelbrot.out) = 5024283fa65866ddd347b877798e84d8" ] ; then echo 'bfi failure!' ; false ; else echo "OK" ; fi

test-mandelbrot: mandelbrot-c mandelbrot-as test-mandelbrot-bfi test-mandelbrot-as test-mandelbrot-c

test-hi1:
	@echo -n "Testing $@	"
	@if [ "`../src/bfi hi.bf`" != 'Hello World!' ] ; then echo 'Grar, failure!' ; false ; else echo "OK" ; fi

test-hi2:
	@echo -n "Testing $@	"
	@if [ "`../src/bfi hilong.bf`" != 'Hello World!' ] ; then echo 'Grar, failure!' ; false ; else echo "OK" ; fi

tests: test-hi1 test-hi2 test-mandelbrot

clean:
	rm -f mandelbrot-as mandelbrot-as.o mandelbrot-as.s mandlebrot.c mandelbrot-c mandelbrot.out
