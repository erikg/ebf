# $Id: Makefile.am,v 1.2 2006/01/03 22:38:05 erik Exp $

extra_DIST=HELLOBF.BF cat.bf hi.bf hilong.bf lame.bf mandelbrot.b random.b wonk.bf

test-mandelbrot:
	@echo -n "Testing $@	"
	@time ../src/bfi mandelbrot.b > mandelbrot.out
	@if [ ! "`md5 mandelbrot.out`" = "MD5 (mandelbrot.out) = 5024283fa65866ddd347b877798e84d8" ] ; then echo 'Grar, failure!' ; false ; else echo "OK" ; fi

test-hi1:
	@echo -n "Testing $@	"
	@if [ "`../src/bfi hi.bf`" != 'Hello World!' ] ; then echo 'Grar, failure!' ; false ; else echo "OK" ; fi

test-hi2:
	@echo -n "Testing $@	"
	@if [ "`../src/bfi hilong.bf`" != 'Hello World!' ] ; then echo 'Grar, failure!' ; false ; else echo "OK" ; fi

tests: test-hi1 test-hi2 test-mandelbrot
