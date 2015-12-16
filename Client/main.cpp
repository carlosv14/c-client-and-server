#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>
#include <iostream>
 #include <cstring>
#include <cstdlib>
#include <regex>
#include "Validations.h"

using namespace std;



 bool validCedula(string id) {
    if( std::regex_match (id, std::regex("\\d{4}-\\d{4}-\\d{5}")))
        return true;
}

bool verifyEmail(string email) {
   return regex_match(email,std::regex("[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,4}"));
}

int main(int argc , char *argv[])
{

    int option = -1;
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
    string complete_message,client_username, client_email,client_name,profilepic,id;

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
        getline(cin,client_username);
        cout<<"Enter E-mail:"<<endl;
        cin>>client_email;
        cout<<"Enter ID:"<<endl;
        cin>>id;
        cout<<"Enter Profile Picture:"<<endl;
        cin>>profilepic;

        complete_message  = "1,name:"+client_name + ",username:" + client_username + ",email:"+ client_email
        +",ID:"+id + ",Profile Pic:" + profilepic;
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
         option=-1;
       /* complete_message  = "username:";
        puts(server_reply);
        scanf("%s" , in);
        complete_message+=in;
        strcpy(message,complete_message.c_str());*/

    }else if(option ==2){
        string searchuser;
        cout<<"Enter Username: "<<endl;
         cin>>searchuser;
         string tosend = "2,username:" + searchuser+",";
        strcpy(message,tosend.c_str());
           if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
           if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
        char * pch = strtok(server_reply,",");
        while(pch!=NULL){
        cout<<pch<<endl;
        pch = strtok(NULL,",");
        }
         option=-1;
    }else if(option ==3){
        string searchuser;
        cout<<"Enter Username: "<<endl;
         cin>>searchuser;
         string tosend = "3,username:" + searchuser+",";
        strcpy(message,tosend.c_str());
           if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
           if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
        puts(server_reply);
         option=-1;
    }else if(option ==4){
        strcpy(message,"4,");
      if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
       exit(0);
    }
}
    close(sock);
    return 0;
}
