#include<stdio.h>#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>
#include <iostream>
 #include <cstring>
#include <cstdlib>
#include <regex>
#include <Users.h>
#include <list>
#include <string>

 //\//
 using namespace std;


 void cleanup(char ** pointer) {
  free(*pointer);
  *pointer = NULL;
}
list<Users> * users = new list<Users>;
int main(int argc , char *argv[])
{
    int option =-1;
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
    char server_message[2000];
    char client_username[100];
    char client_email[100];
    char client_name[100];

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");

    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {

       strcpy(server_message,"User Succesfully Added!");
       write(client_sock , server_message , strlen(server_message));
          char * pch;
          pch = strtok (client_message,",");
          while (pch != NULL)
          {
            printf ("%s\n",pch);
            pch = strtok (NULL, ",");
          }


    }

    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }

    return 0;
}

