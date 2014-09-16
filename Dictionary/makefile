# April Dawn Kester
# akester
# CMPS 12M
# August 7, 2013
# Compiles with Macros
# makefile for Dictionary.c
# No special instructions

FLAGS   = -std=c99 -Wall
SOURCES = Dictionary.c DictionaryClient.c
OBJECTS = Dictionary.o DictionaryClient.o
HEADERS = Dictionary.h
EXEBIN  = DictionaryClient
SUBMIT = submit cmps012b-pt.u13 lab5
FILES = README makefile DictionaryTest.c $(SOURCES) $(HEADERS)

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full $(EXEBIN) 

submit: $(FILES)
	$(SUBMIT) $(FILES)

diff:
	diff out DictionaryClientOut
