//April Dawn Kester & Shane McVeigh
//akester & smcveigh
//CMPE 150
//March 5, 2014
//Final Project
//C program to establish server using TCP

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

//Function to print a warning to stderr
void warning(char *msg)
{
   fprintf(stderr, msg);
}

//Function to print error message based on value of errno
//NOTE: This exits the program
void error(char *msg)
{
   perror(msg);
   exit(1);
}

//Trim all whitespace characters on the right of a string
void rtrim(char* string) {
   int i=0;
   int start = strlen(string);
   printf("start: %d\t%s\tlastchar=%d\n", start, string, string[start]);
   for(i=start; i>=0; i--) {
      if(!(string[i]=='\n' || string[i]=='\r' || string[i]=='\0')) {
         if(i<start) 
            string[i+1] = '\0';
         break;
      }
   }
}

int main(int argc, char *argv[])
{

   int listener, newfd, portno; 
   socklen_t clilen;
   fd_set master, read_fds;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n;

   if (argc < 2)
   {
      fprintf(stderr,"ERROR, no port provided\n");
      exit(1);
   }

    //set up the listener socket
   listener = socket(AF_INET, SOCK_STREAM, 0);

   if (listener < 0)
   {
      //unable to set up listener socket
      error("ERROR opening socket");
   }
   
   int yes=1;
   setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

   bzero((char *) &serv_addr, sizeof(serv_addr));

   portno = atoi(argv[1]);
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);

   if (bind(listener, 
               (struct sockaddr *) &serv_addr,
               sizeof(serv_addr)) < 0)
   {
      //unable to bind port
      error("ERROR on binding");
   }

   if(listen(listener,5) == -1) {
      error("Error listening for connections!");
   }

   FD_SET(listener, &master); //add listener to the list of sockets to be serviced
   
   clilen = sizeof(cli_addr);
   int fdmax = listener;

   int count=0;
   for(count=0;;count++) {
      //print the number of completed loops (debug info)
      printf("j=%d\n", count);
      read_fds = master;
	  
	  //select 
      if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
         error("Error calling select()");
      }
      
      printf("Selected..\n");
      int socketNum=0;
      for(socketNum=0; socketNum<=fdmax; socketNum++) {
         if(FD_ISSET(socketNum, &read_fds)) {
            if(socketNum==listener) {
               //handle new connections
               printf("Accepting new connection (%d)\n", socketNum);
               newfd = accept(listener,
                              (struct sockaddr *) &cli_addr, 
                              &clilen);
   
               if (newfd < 0)
               {
                  error("ERROR on accept");
               }
               
               else {
			      //Add the new connection to the socket list
                  FD_SET(newfd, &master);
                  if(newfd > fdmax) {
                     fdmax = newfd;
                  }
               }
            }
            
            else {
			   //empty the buffer
               bzero(buffer,256);
			   
               printf("Receiving...\n");
               n = recv(socketNum, buffer, 255, 0);
               if(n<=0) {
                  if(n == 0) { //client closed the connection
                     printf("closing connection %d\n", socketNum);
                  }   

                  if (n < 0) { //an error occured
                     warning("ERROR reading from socket\n");
                  }
                  
                  // either an error has occurred or the client 
                  //is finished - close the socket
                  close(socketNum); 
                  FD_CLR(socketNum, &master);
               }

               else {
                  printf("Received %d bytes\n", n);

                  rtrim(buffer);

                  if(strcmp(buffer, "shutdown") == 0 || 
                              strlen(buffer)==0) {
                     printf("Received command <%s>. ", buffer);
					 close(socketNum);
					 FD_CLR(socketNum, &master);
                     printf("Closed connection.\n");
                     break;
                  }
                  
                  char temp[sizeof(buffer)/sizeof(buffer[0])];
                  int charCnt=0;
                  int containsAnd = 0;
                  for(charCnt=0; charCnt< strlen(buffer); charCnt++) {
                     if(buffer[charCnt] == '&') {
                        containsAnd = 1;
                        break;
                     }
                  }

                  char line[256];
                  if(containsAnd) {
                     system(buffer);
                  }

                  else {
                     strcpy(temp, "(");
                     strcat(temp, buffer);
                     strcat(temp, ") 2>&1");
                     strcpy(buffer, temp);
                     FILE* pipe = (FILE*)popen(buffer, "r");
   
                     if(pipe==NULL || pipe==(FILE*)-1) {
                        warning("ERROR: problem creating the pipe..\n");
                     }
                     else {
                        while (fgets(line, sizeof(line), pipe)) {
                           line[sizeof(line)/sizeof(line[0])] = '\0';
                           n = send(socketNum, line, sizeof(line), MSG_NOSIGNAL); 
                           printf("sending %5d bytes: %s\n", n, line);

                           if (n < 0)
                           {
                              printf("ERROR Writing to socket\n");
                              warning("ERROR writing to socket\n");
                              break;
                           }
                        }
                     }
                     pclose(pipe);
                  }

				  //send delimiter to mark the end of command output
                  strcpy(line, "\r\n\0");
                  n = send(socketNum, line, strlen(line), MSG_NOSIGNAL);
                  if (n < 0)
                  {
                     warning("Error writing delimiter to socket\n");
                  }
               }
            }
         }
         else {
            printf("nothing to receive..\n");
         }
      }
   }
   close(listener);

   return 0;
}
