//April Dawn Kester & Shane McVeigh
//akester & smcveigh
//CMPE 150                                                                    
//March 5, 2014  
//Final Project
//README

How to run and compile code:
Run "make" command to run the included Makefile.
Source code is located in /src, makefile is included in the main directory. 
Make will compile code using gcc -Wall, and output the files to the /bin directory.
Make also uses mkdir to create the /bin if necessary.

Running programs::
./bin/server <port>
./bin/client <port> <ipaddress>

Explanation of how client and server communicate:

SERVER
1. socket()		create socket, and store the returned descriptor for future reference
2. bind()		bind the socket to the specified port number
3. listen()		listen for connection requests from clients

CLIENT
4. socket()		create socket, and store the returned descriptor for future reference
5. connect()	connect a socket (specified by the descriptor), to an ip address and port (which is the server).

SERVER
6. select()		loop through every active socket in our list, and either process the command, or accept a new connection
7. accept()		as incoming connections are requested, accept them, and add them to the list of sockets to be serviced

CLIENT & SERVER
8. read/write()	send/receive data
9. close() 		socket descriptor is deallocated, final close handshake, socket structure deallocated.

10. shutdown() 	allows sender/receiver to shutdown independently


Sources:
For this project, we did a lot of research, including examining and attempting to understand examples available on the web.
Our main source of code examples in this project was "Beej's Guide to Network Programming: Using Internet Sockets" (beej.us).
In particular, we reference:
select()		http://www.beej.us/guide/bgnet/output/html/multipage/selectman.html
bind()			http://www.beej.us/guide/bgnet/output/html/multipage/bindman.html
