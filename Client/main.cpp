#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>
#include <iostream>
 #include <cstring>
#include <cstdlib>
#include "Validations.h"

using namespace std;


int main(int argc , char *argv[])
{

    int option = -1;
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
    string complete_message,client_username, client_email,client_name,Profilepic,id;

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    //keep communicating with server
    while(1)
    {
    if(option == -1){
        printf("Enter message : ");
        scanf("%s" , message);
        option = atoi(message);
    }else if(option == 1){
        //%s
        //Send some data
        cin.ignore();
        cout<<"Enter Name:"<<endl;
        getline(cin,client_name);
        cout<<"Enter Username: "<<endl;
        cin>>client_username;
        while(true){
        cout<<"Enter E-mail:"<<endl;
        cin>>client_email;
        if(Validations::verifyEmail(client_email));
            break;
        };



        complete_message  = "name:"+client_name + ",username:" + client_username + ",email:"+ client_email;
        strcpy(message,complete_message.c_str());
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }

        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
         puts(server_reply);
       /* complete_message  = "username:";
        puts(server_reply);
        scanf("%s" , in);
        complete_message+=in;
        strcpy(message,complete_message.c_str());*/

    }
}
    close(sock);
    return 0;
}
