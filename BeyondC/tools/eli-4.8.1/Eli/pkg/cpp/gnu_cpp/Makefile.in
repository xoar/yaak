all:	cpp.exe

tidy:
	rm -f *.o

clean:	tidy
	rm -f cpp.exe

distclean:	clean
	rm -f Makefile config.h config.cache config.log config.status

cpp.exe:	cccp.o cexp.o obstack.o version.o
	$(CC) -o cpp.exe cccp.o cexp.o obstack.o version.o
