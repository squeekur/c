GCC = gcc -Wall -g
MAKEDIR = -@mkdir -p
BINDIR = ./bin

all: server client

server: directory ./src/server.c
	$(GCC) ./src/server.c -o ./bin/server

client: directory ./src/client.c
	$(GCC) ./src/client.c -o ./bin/client

directory: $(BINDIR)
	$(MAKEDIR) $(BINDIR)
