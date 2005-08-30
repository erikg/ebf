
bf2c: bf2c.o
	$(CC) -o bf2c bf2c.o

bfi: bfi.o
	$(CC) -o bfi bfi.o

clean:
	rm -f bfi bfi.o bf2c bf2c.o
