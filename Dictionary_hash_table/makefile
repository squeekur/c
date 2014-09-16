# April Dawn Kester
# akester
# CMPS 12B
# August 15, 2013
# compiles, utility functions
# makefile for DictionaryClient.c
# No special instructions

FLAGS   = -std=c99 -Wall
SOURCES = Dictionary.c DictionaryClient.c
FILES	= README makefile Dictionary.h DictionaryTest.c
OBJECTS = Dictionary.o DictionaryClient.o
HEADERS = Dictionary.h
EXEBIN  = DictionaryClient
SUBMIT	= submit cmps012b-pt.u13 pa5 

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full $(EXEBIN) 

submit: ${SOURCES}
	${SUBMIT} ${SOURCES} ${FILES}

diff:
	diff out model-out