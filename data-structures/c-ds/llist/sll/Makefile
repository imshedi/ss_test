## Author	Shreenidhi Shedi
## Date		14th Sep 2014

CC = gcc
CC_FLAG = -Wall -c -g

EXEC	= sll
SOURCES	= $(notdir $(wildcard ./src/*.c))
OBJECTS	= $(SOURCES:.c=.o)
INC	= -I ./hdr/
HDR	= ./hdr/*.h

.PHONY : clean
vpath %.c = ./src/
vpath %.o = ./obj/

## Main target
$(EXEC) : $(OBJECTS)
	@$(CC) $^ -o $@ $(INC)
	@mv ./*.o ./obj/

## To obtain object files
%.o : %.c $(HDR)
	@$(CC) $(CC_FLAG) $< $(INC)

clean :
	 @clear && rm -rf ./$(EXEC) ./obj/*.o ./*/*~ ./*~ ./a.out
