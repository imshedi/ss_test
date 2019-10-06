CC = gcc
HDR = *.h
INC = -I .
EXEC = lzw.out
CFLAGS = -Wall -g
SOURCES = $(notdir $(wildcard *.c))

.PHONY : clean
vpath %.c = ./

$(EXEC) : $(SOURCES) $(HDR)
	$(CC) $(CFLAGS) $(SOURCES) -o $@ $(INC)

tags:
	ctags -R
	cscope -Rb

clean :
	rm -f $(EXEC) *.o

distclean:
	rm -f $(shell ls -I "*.c" -I "*.h" -I "*.sh" -I "Makefile")
	clear
