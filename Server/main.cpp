#include<stdio.h>
#include<string.h>    //strlen
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
#include <fstream>

 //\//
 using namespace std;


 void cleanup(char ** pointer) {
  free(*pointer);
  *pointer = NULL;
}
Users arr [20];
int main(int argc , char *argv[])
{
    int cant_users=0;
    int option =-1;
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
    char server_message[2000];
    string complete_message;

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


        option = atoi(strtok (client_message,","));
        if(option == 1){
        arr[cant_users].name=strtok (NULL, ",");
        arr[cant_users].username = strtok (NULL, ",");
        arr[cant_users].email = strtok (NULL, ",");
        arr[cant_users].id = strtok (NULL, ",");
        arr[cant_users].profilepic = strtok (NULL, ",");
        if(cant_users<20)
        cant_users++;
        strcpy(server_message,"User Succesfully Added!");
        write(client_sock , server_message , strlen(server_message));
        option=0;
        }else if(option ==2 ){
        bool found = false;
        string username = strtok(NULL,",");
        cout<<"this username: "<<username<<endl;
        for(int i = 0; i<cant_users;i++){
            if(username == arr[i].username){
                found = true;
                complete_message = arr[i].username + "," + arr[i].name +","+arr[i].email + "," + arr[i].profilepic;
                break;
            }
        }
        if(!found){
        strcpy(server_message,"User Not Found!        ");
        }else{
        strcpy(server_message,complete_message.c_str());
        }
        write(client_sock , server_message , strlen(server_message));
        option = 0;
        }else if(option ==3 ){
        bool found = false;
        string username = strtok(NULL,",");
        cout<<"this username: "<<username<<endl;
        for(int i = 0; i<cant_users;i++){
            if(username == arr[i].username){
                found = true;
                arr[i].name="";
                arr[i].username = "";
                arr[i].email = "";
                arr[i].id = "";
                arr[i].profilepic = "";
                complete_message = "Successfully deleted ";
                break;
            }
        }
        if(!found){
        strcpy(server_message,"User Not Found!        ");
        }else{
        strcpy(server_message,complete_message.c_str());
        }
        write(client_sock , server_message , strlen(server_message));
        option = 0;
        }else if(option ==4 ){
        ofstream usersfile;
        usersfile.open ("users.txt",ios::ate);
        if(usersfile.is_open()) {
           for(int i = 0; i<20;i++){
                usersfile<<"{"+  arr[i].name +"," + arr[i].username + "," + arr[i].email + "," + arr[i].profilepic + ","+ arr[i].id + "}"<<"\n";
            }
            usersfile.close();
        }

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

