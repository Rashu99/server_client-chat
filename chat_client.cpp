#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>      /* Headers file needed for Socket Programming */
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define portNum 3000      /* portNum is same for server and client */
#define ip "127.0.0.1"

using namespace std;

int main()
{
     int sockfd;          /* This variable contain value return by soccket function */
     int n = 1024;
     char msg[n];
    
     bool isExit = false;
 
     

     struct sockaddr_in addr;     

    /* sockaddr_in , this structure is already defined,
       A parallel structure that makes it easy to 
       reference elements of the socket address */


                                                  /* socket() function */

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     
     if (sockfd == -1)
     {
         cout<<"\nThere is an Error \n";
         exit(-1);
     }

     cout << "\n=> Socket client has been created..." << endl;
     
     addr.sin_family = AF_INET;
     addr.sin_port = htons(portNum);

              
                                         /* connect() function */

     connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
   
    /* Connects to a remote host
       sockfd is the socket descriptor returned by socket()
       addr is pointer to struct sockaddr that 
       contains information on destination IP address and 
       port

       addrlen is set to sizeof(struct sockaddr)
 
      */

     cout<<" \n Awaiting confirmation from server...";
                   
                              
                                              /* recv() and send() function */
                 
     
     recv(sockfd, msg, n, 0);
     cout<<"\n connection confirmed...";

     cout<<"\n Press * after a message \n Press # to end the connection \n";

     do {
          cout<<"Client: ";
          do{
              cin>>msg;
              send(sockfd, msg, n, 0);
              if (*msg == '#'){
                  send(sockfd, msg, n, 0);
                  *msg = '*';
                  isExit = true;
              }
           }while (*msg != '*');

           cout<< "Server: ";
           do {
               recv(sockfd, msg, n, 0);
               cout<<msg<<" ";
               if (*msg == '#') {
                   *msg = '*';
                   isExit = true;
               }
            } while (*msg != '*');
            cout<< endl;
     } while (!isExit);
 
                                                      /* Close function() */

   close(sockfd);
   return 0;
}
