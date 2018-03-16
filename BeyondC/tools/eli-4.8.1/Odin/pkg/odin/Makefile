FILES = if-bcast.o if-build.o if-candrv.o if-client.o if-cmd.o \
  if-depend.o if-drvgrf.o if-dir.o if-drvpth.o if-drvspc.o \
  if-edg.o if-env.o if-err.o if-exec.o if-execint.o if-execspc.o \
  if-fhacc.o if-fhnam.o if-fhnew.o if-fhsrc.o if-fhstat.o \
  if-file.o if-filelm.o if-filhdr.o if-filinp.o if-filprm.o if-filpval.o \
  if-filtyp.o if-ft.o if-get.o if-help.o if-hook.o \
  if-info.o if-io.o if-ipc.o if-lex.o if-lvl.o if-main.o \
  if-nod.o if-oclex.o if-pfilhdr.o if-prmtyp.o if-rbs.o \
  if-symbol.o if-sysdep.o if-system.o if-systools.o \
  if-update.o if-util.o if-var.o if-yylex.o \
  boot/fsys-yacc.o boot/client-yacc.o boot/default-dg.o \
  boot/stub-in.o boot/stub-out.o \
  editline/editline.o editline/complete.o editline/sysunix.o

all: nested odin.exe

nested:
	(cd boot; make CC=$(CC) CFLAGS='$(CFLAGS)');
	(cd editline; make CC=$(CC) CFLAGS='$(CFLAGS)')

odin.exe: $(FILES)
	- $(CC) $(CFLAGS) $(LDFLAGS) -o odin.exe $(FILES) \
         `if [ $$ODINBOOT_CONFIG ] ; then echo $$ODINBOOT_SOCKET_LIBS; \
	  elif [ -f /usr/lib/libsocket.* ] ; then echo '-lsocket -lnsl'; \
	  else true; fi`

clean:
	rm -f *.o */*.o *.exe
