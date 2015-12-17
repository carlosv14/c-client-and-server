#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>
#include <iostream>
 #include <cstring>
#include <cstdlib>
#include <regex>

using namespace std;



 bool validCedula(string id) {
   return regex_match (id, std::regex("\\d{4}-\\d{4}-\\d{5}"));
}

bool validEmail(string email) {
   return regex_match(email,std::regex("[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,4}"));
}


bool validDate(string date) {
    return regex_match (date, std::regex("\\d{2}-\\d{2}-\\d{4}"));

}

int main(int argc , char *argv[])
{

    int option = -1;
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
    string complete_message,client_username, client_email,client_name,profilepic,id,bd;


    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );


    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    while(1)
    {
    if(option == -1){
        cout<<"1. Add User"<<endl;
        cout<<"2. Search User"<<endl;
        cout<<"3. Delete User"<<endl;
        cout<<"4. Exit"<<endl;
        printf("Enter message : ");
        scanf("%s" , message);
        option = atoi(message);
    }else if(option == 1){

        cin.ignore();
        cout<<"Enter Name:"<<endl;
        getline(cin,client_name);
        cout<<"Enter Username: "<<endl;
        getline(cin,client_username);
        while(true) {
            cout << "Enter E-mail:" << endl;
            cin >> client_email;
       //     if(validEmail(client_email))
                    break;
        }
        while(true) {
            cout << "Enter ID:" << endl;
            cin >> id;
         //   if(validCedula(id))
                break;
        }

        while(true) {
            cout << "Enter Birth Date:" << endl;
            cin >> bd;
           // if(validDate(bd))
                break;
        }
        cout<<"Enter Profile Picture:"<<endl;
        cin>>profilepic;

        complete_message  = "1,name:"+client_name + ",username:" + client_username + ",email:"+ client_email
        +",ID:"+id + ",Profile Pic:" + profilepic + ",Birthdate:" + bd;
          bzero(message,1000);
        strcpy(message,complete_message.c_str());
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }

        bzero(server_reply,2000);
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
           bzero(message,1000);
        strcpy(message,tosend.c_str());
           if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        bzero(server_reply,2000);
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
           bzero(message,2000);
        strcpy(message,tosend.c_str());
           if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        bzero(server_reply,2000);
           if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
        puts(server_reply);
         option=-1;
    }else if(option ==4){
      bzero(message,2000);
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
