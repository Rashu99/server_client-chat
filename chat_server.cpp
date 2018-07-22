#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>               /* Headers file needed for Socket Programming */
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define portNum 3000                    /* portNum is same for server and client */


 
using namespace std;

int main()
{

   int sockfd, server;
   bool isExit = false;
   int n = 1024;
   char msg[n];
   

   

   struct sockaddr_in addr;
    
     /* sockaddr_in , this structure is already defined,
       A parallel structure that makes it easy to 
       reference elements of the socket address */
  
   socklen_t size;
   

   sockfd = socket(AF_INET, SOCK_STREAM, 0);

   if (sockfd < 0)
   {
      cout<< "\n There is an Error \n";
      exit(-1);
   }

   cout << "\n=> Server socket has been created..." << endl;
   
   addr.sin_family = AF_INET;
   addr.sin_port = htons(portNum);
   addr.sin_addr.s_addr = htons(INADDR_ANY);


                                                /* bind() function */

   bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

   /* Used to associate a socket with a port on the local 
      machine
      sockfd is the socket descriptor returned by socket()

      my_addr is pointer to struct sockaddr that contains 
      information about your IP address and port

      addrlen is set to sizeof(struct sockaddr)
*/

   size = sizeof(addr);
   cout << "=> Looking for clients..." << endl;


                                          /* listen() and accept() function */

   listen(sockfd, 1);

   int clientcount = 1;

   server = accept(sockfd, (struct sockaddr *)&addr, &size);


    /* Waits for incoming connections

       int listen(int sockfd, int backlog);

       sockfd is the socket file descriptor returned by socket() 

       backlog is the number of connections allowed on 
       the incoming queue

       listen() returns -1 on error

       Need to call bind() before you can listen()  */

     /* accept() gets the pending connection on the port you are listen()ing on

        int accept(int sockfd, void *addr, int *addrlen);
        
        sockfd is the listening socket descriptor

        information about incoming connection is stored in 
        addr which is a pointer to a local struct sockaddr_in

        addrlen is set to sizeof(struct sockaddr_in */
   



                                          /* send() and recv() function */ 

   while (server > 0)
   { 

       strcpy(msg, "=> Server connected...\n");
       send(server, msg, n, 0);
       cout<<"Client: ";
       do {
           recv(server, msg, n, 0);
           cout<<msg<<" ";
           if (*msg == '#') {
               *msg = '*';
               isExit = true;
           }
        }while (*msg != '*');
     
        do {
            cout<<"\nServer: ";
            do {
                cin>>msg;
                send(server, msg, n, 0);
                if (*msg == '#') {
                  send(server, msg, n, 0);
                  *msg = '*';
                  isExit = true;
                }
              } while (*msg != '*');

              cout << "client: ";
              do {
                  recv(server, msg, n, 0);
                  cout<<msg<<" ";
                  if(*msg == '#') {
                     *msg == '*';
                     isExit = true;
                  }
               } while (*msg != '*');
            } while(!isExit);

  
      /* 
            Once a connection has been established, both ends 
            can both read and write to the connection. Naturally, 
            everything written by the client will be read by the 
            server, and everything written by the server will be 
            read by the client.
        */

        /* ---------------- CLOSE CALL ------------- */
        /* ----------------- close() --------------- */

        /* 
            Once the server presses # to end the connection,
            the loop will break and it will close the server 
            socket connection and the client connection.
        */

            cout << "\n\n=> Connection terminated with IP " << inet_ntoa(addr.sin_addr);
            close(server);
            isExit = false;
            exit(-1);
        }
        
        close(sockfd);
        return 0;
}
              
