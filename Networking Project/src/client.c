//April Dawn Kester & Shane McVeigh
//akester & smcveigh
//CMPE 150
//March 5, 2014  
//Final Project
//C program to connect to remote server using TCP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

void error(char *msg) //function to print error message
{   
   perror(msg); //verified perror reports to stderr 
   exit(0);
   }

int main(int argc, char *argv[]) //args required IP and port
{ 
   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;

   char buffer[256]; //send and recieve values to the server

   if (argc < 3) //error checking for 3 command line arguments
   {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }

   portno = atoi(argv[1]); 
   //get port number, stored as char[] cast as int

   sockfd = socket(AF_INET, SOCK_STREAM, 0); 
   //create socket descripter (int family, int type, int protocol) 
   //0 to select the system's default

   if (sockfd < 0) //error checking for empty socket, will return -1   
   {
      error("ERROR opening socket");
   }

   server = gethostbyname(argv[2]); //get server address
   if (server == NULL) //error checking for server address
   {
      fprintf(stderr, "ERROR! No such host\n");
      exit(0);
   }

   bzero((char *) &serv_addr, sizeof(serv_addr)); //clear server address
   serv_addr.sin_family = AF_INET;

   bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length); 
   //copying values of server address

   serv_addr.sin_port = htons(portno); 
   //converting port number integer to network address


   if (connect(sockfd,
               (struct sockaddr*)&serv_addr,
               sizeof(serv_addr)) < 0)
   //connect (int sockfd, struct sockaddr *serv_addr, int addrlen), 
   //will return -1 if unable to connect
   {
      error("ERROR connecting");
   }
   
   while(1==1)
   {
   printf("Please enter the command: "); //print to stdout
   
   bzero(buffer,256); //clear buffer
   fgets(buffer,255,stdin); //fill buffer from stdin

   n = send(sockfd,buffer,strlen(buffer),0); 
   //write to socket from buffer

   if (n < 0) //return -1 if fail
   {
      error("ERROR writing to socket");
   }
   
   char test[20];
   strcpy(test, "shutdown\n\0");
   
   
   if (strcmp(buffer, test) == 0) 
   //if command is shutdown close connection and halt program
   {
      printf("goodbye\n");
      close(sockfd);
      return 0;
   }

   do {
      bzero(buffer,256); //clear buffer

      n = recv(sockfd,buffer,256,MSG_DONTWAIT); 
      //read from socket to buffer
      
      if (n == 0)
      {
         printf("session terminated by server\n");
         close(sockfd);
         return 0;
      }

      char delim[20];
      strcpy(delim, "\r\n\0");
      if (n < 0 && errno != EAGAIN) //return -1 if fail
      {
         error("ERROR reading from socket");
      }
      
      if(strcmp(buffer, delim)==0) break;
      printf("%s",buffer);
      
   } while(n > 0 || errno == EAGAIN); //will return 0 when finished 
   //create socket descripter (int family, int type, int protocol) 
   //0 to select the system's default

   if (sockfd < 0) //error checking for empty socket, will return -1   
   {
      error("ERROR opening socket");
   }

   server = gethostbyname(argv[2]); //get server address
   if (server == NULL) //error checking for server address
   {
      fprintf(stderr, "ERROR! No such host\n");
      exit(0);
   }

   bzero((char *) &serv_addr, sizeof(serv_addr)); //clear server address
   serv_addr.sin_family = AF_INET;

   bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length); 
   //copying values of server address

   }
   
   close(sockfd); //close socket
   return 0; //end program
}

