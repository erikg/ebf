GEN_SRCS=hi.c random.c mandelbrot.c cat.c HELLOBF.c
OBJ=bfi.o bf2c.o
BINS=hi random mandelbrot cat HELLOBF bfi bf2c

all: HELLOBF hi random mandelbrot cat bfi

HELLOBF: HELLOBF.c
	$(CC) -o HELLOBF HELLOBF.c
HELLOBF.c: HELLOBF.BF bf2c
	./bf2c HELLOBF.BF

hi: hi.c
	$(CC) -o hi hi.c
hi.c: hi.bf bf2c
	./bf2c hi.bf

random: random.c
	$(CC) -o random random.c
random.c: random.b bf2c
	./bf2c random.b

mandelbrot: mandelbrot.c
	$(CC) -o mandelbrot mandelbrot.c
mandelbrot.c: mandelbrot.b bf2c
	./bf2c mandelbrot.b

cat: cat.c
	$(CC) -o cat cat.c
cat.c: cat.bf bf2c
	./bf2c cat.bf

bf2c: bf2c.o
	$(CC) -o bf2c bf2c.o

bfi: bfi.o lex.o parser.o eval.o
	$(CC) -o bfi bfi.o lex.o parser.o eval.o

clean:
	rm -f $(OBJ) $(BINS) $(GEN_SRCS)


