#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <iostream>
 #include <cstring>
#include <cstdlib>
#include <regex>
#include "Users.h"
#include <list>
#include <string>
#include <fstream>

 //\//
 using namespace std;


vector<Users> arr = {};
vector<string> SplitString(string word, char token){
    vector<string> result = {};
    string to_add = "";
    for(char c : word){
        if (c != token) {
            to_add += c;
        }
        else{
            result.push_back(to_add);
            to_add = "";
        }
    }
    result.push_back(to_add);
    return result;
}


void fillArray(string users){
vector<string> allUsers = SplitString(users,'|');
int i = 0;
for(string s:allUsers){
vector<string> user = SplitString(s,',');
Users u;
u.name= user[0];
u.username = user[1];
u.email = user[2];
u.id = user[3];
u.profilepic = user[4];
u.bd = user[5];
    arr.push_back(u);
    }
}


void loadFromFile(){
string allusers = "";
string line;
ifstream usersfile("users.txt",ios::out);
if(usersfile.is_open()){
while(getline(usersfile,line))
{
    allusers+=line;
}
usersfile.close();
}
    if(allusers!="")
    fillArray(allusers);
}

int main(int argc , char *argv[])
{
    loadFromFile();
    int cant_users=0;
    int option =-1;
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
    char server_message[2000];
    string complete_message;


    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );


    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");


    listen(socket_desc , 3);


    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);





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
        Users u;
        u.name=strtok (NULL, ",");
        u.username = strtok (NULL, ",");
        u.email = strtok (NULL, ",");
        u.id = strtok (NULL, ",");
        u.profilepic = strtok (NULL, ",");
        u.bd = strtok(NULL,",");
        bool found = false;
         bzero(server_message,2000);
        for(int i = 0; i<arr.size();i++){
            if(arr[i].username == u.username){
                found = true;
                  strcpy(server_message,"Username is already in use !");
                break;
           } if(arr[i].id == u.id ){
                found = true;
                strcpy(server_message,"ID is already in use !");
                break;
            }if(arr[i].email == u.email){
                found = true;
                strcpy(server_message,"Email is already in use !");
                break;
                }

        }

        if(!found){
            arr.push_back(u);
            strcpy(server_message,"User Succesfully Added!");

        }


        write(client_sock , server_message , strlen(server_message));
        option=0;
        }else if(option ==2 ){
        bool found = false;
        string username = strtok(NULL,",");
        cout<<"this username: "<<username<<endl;
        for(int i = 0; i<arr.size();i++){
            if(username == arr[i].username){
                found = true;
                complete_message = arr[i].username + "," + arr[i].name +","+arr[i].email + "," + arr[i].profilepic + "," + arr[i].bd;
                break;
            }
        }
        if(!found){
          bzero(server_message,2000);
        strcpy(server_message,"User Not Found!        ");
        }else{
          bzero(server_message,2000);
        strcpy(server_message,complete_message.c_str());
        }
        write(client_sock , server_message , strlen(server_message));
        option = 0;
        }else if(option ==3 ){
        bool found = false;
        string username = strtok(NULL,",");
        cout<<"this username: "<<username<<endl;
        for(int i = 0; i<arr.size();i++){
            if(username == arr[i].username){
                found = true;
                arr.erase(arr.begin()+i);
                complete_message = "Successfully deleted ";
                break;
            }
        }
        if(!found){
          bzero(server_message,2000);
        strcpy(server_message,"User Not Found!        ");
        }else{
          bzero(server_message,2000);
        strcpy(server_message,complete_message.c_str());
        }
        write(client_sock , server_message , strlen(server_message));
        option = 0;
        }else if(option ==4 ){
        ofstream usersfile;
        usersfile.open ("users.txt",ios::in);
        usersfile.clear();
        if(usersfile.is_open()) {
           for(int i = 0; i<arr.size();i++){
                usersfile<< arr[i].name +"," + arr[i].username + "," + arr[i].email + "," + arr[i].profilepic + ","+ arr[i].id+ ","+arr[i].bd;
                if(i<arr.size()-1)
                usersfile<<"|";
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
