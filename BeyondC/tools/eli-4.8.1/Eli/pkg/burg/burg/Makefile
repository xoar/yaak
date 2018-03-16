# $Id: Makefile,v 1.3 2000/08/10 00:08:31 waite Exp $

CFLAGS	=
#CFLAGS	= -O
#CFLAGS	= -O -DNOLEX
#CFLAGS	= -g -DDEBUG
#CFLAGS	= -g -DNOLEX -DDEBUG

SRCS = \
	be.c \
	burs.c \
	closure.c \
	delta.c \
	fe.c \
	item.c \
	lex.c \
	list.c \
	main.c \
	map.c \
	nonterminal.c \
	operator.c \
	pattern.c \
	plank.c \
	queue.c \
	rule.c \
	string.c \
	symtab.c \
	table.c \
	trim.c \
	zalloc.c

BU_OBJS = \
	burs.o \
	closure.o \
	delta.o \
	item.o \
	list.o \
	map.o \
	nonterminal.o \
	operator.o \
	pattern.o \
	queue.o \
	rule.o \
	table.o \
	trim.o \
	zalloc.o

FE_OBJS = \
	be.o \
	fe.o \
	lex.o \
	main.o \
	plank.o \
	string.o \
	symtab.o \
	y.tab.o

all: burg.exe

burg.exe: $(BU_OBJS) $(FE_OBJS)
	$(CC) -o burg.exe $(CFLAGS) $(BU_OBJS) $(FE_OBJS)

#y.tab.c y.tab.h: gram.y
#	yacc -d gram.y

tidy:
	rm -f *.o core *.aux *.log *.dvi sample sample.c tmp

clean:
	rm -f *.o core burg.exe *.aux *.log *.dvi sample sample.c tmp

$(FE_OBJS):	b.h
$(BU_OBJS):	b.h
$(FE_OBJS):	fe.h

lex.o:	y.tab.h

doc.dvi: doc.tex
	latex doc; latex doc

test: burg.exe sample.gr
	./burg.exe -I     <sample.gr   >sample.c && $(CC) $(CFLAGS) -o sample sample.c && ./sample
	./burg.exe -I      sample.gr   >tmp && cmp tmp sample.c
	./burg.exe -I     <sample.gr -o tmp && cmp tmp sample.c
	./burg.exe -I      sample.gr -o tmp && cmp tmp sample.c
	./burg.exe -I -O0 <sample.gr   >tmp && cmp tmp sample.c
	./burg.exe -I -=  <sample.gr   >tmp && cmp tmp sample.c
