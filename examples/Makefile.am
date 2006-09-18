# $Id: Makefile.am,v 1.3 2006/09/18 13:36:51 erik Exp $

extra_DIST=HELLOBF.BF cat.bf hi.bf hilong.bf lame.bf mandelbrot.b random.b wonk.bf

test-mandelbrot-c:
	@echo -n "Testing $@	"
	@../src/bf2c mandelbrot.b
	@gcc -O3 -o mandelbrot mandelbrot.c
	@time ./mandelbrot > mandelbrot.out
	@if [ ! "`md5 mandelbrot.out`" = "MD5 (mandelbrot.out) = 5024283fa65866ddd347b877798e84d8" ] ; then echo 'bfi failure!' ; false ; else echo "OK" ; fi
	@rm mandelbrot mandelbrot.out mandelbrot.c mandelbrot.o

test-mandelbrot-as:
	@echo -n "Testing $@	"
	@../src/bf2as mandelbrot.b > mandelbrot.s
	@as -o mandelbrot.o mandelbrot.s
	@ld -o mandelbrot mandelbrot.o
	@time ./mandelbrot > mandelbrot.out
	@if [ ! "`md5 mandelbrot.out`" = "MD5 (mandelbrot.out) = 5024283fa65866ddd347b877798e84d8" ] ; then echo 'bfi failure!' ; false ; else echo "OK" ; fi
	@rm mandelbrot mandelbrot.out mandelbrot.s mandelbrot.o

test-mandelbrot-bfi:
	@echo -n "Testing $@	"
	@time ../src/bfi mandelbrot.b > mandelbrot.out
	@if [ ! "`md5 mandelbrot.out`" = "MD5 (mandelbrot.out) = 5024283fa65866ddd347b877798e84d8" ] ; then echo 'bfi failure!' ; false ; else echo "OK" ; fi
	@rm mandelbrot.out

test-mandelbrot: test-mandelbrot test-mandelbrot-as test-mandelbrot-c

test-hi1:
	@echo -n "Testing $@	"
	@if [ "`../src/bfi hi.bf`" != 'Hello World!' ] ; then echo 'Grar, failure!' ; false ; else echo "OK" ; fi

test-hi2:
	@echo -n "Testing $@	"
	@if [ "`../src/bfi hilong.bf`" != 'Hello World!' ] ; then echo 'Grar, failure!' ; false ; else echo "OK" ; fi

tests: test-hi1 test-hi2 test-mandelbrot
