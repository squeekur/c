# April Dawn Kester
# akester
# CMPS 12M
# July 24, 2013
# Compiles with Macros
# makefile for FileReverse.c
# No special instructions

FLAGS = -std=c99 -Wall
SOURCES = charType.c
OBJECTS = charType.o
EXEBIN = charType
SUBMIT = submit cmps012b-pt.u13 lab4
FILES = README makefile $(SOURCES)

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean:
	rm -f $(EXEBIN) $(OBJECTS)

submit: $(FILES)
	$(SUBMIT) $(FILES)

check:
	valgrind --leak-check=full $(EXEBIN) $(SOURCES) out

diff:
	diff out model-out

