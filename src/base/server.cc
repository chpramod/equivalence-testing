#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <bits/stdc++.h>
#include <dirent.h>
#include <netinet/tcp.h>

#include "base/server.h"
using std::cout;
using std::endl;

#define SEND_SIZE 1024

int serverFileDescriptor;
int clientFileDescriptor;

void socket_pair(){
    serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    
    if(serverFileDescriptor<0){
        cout<<"Couldn't create socket\n";
        return;
    }

    int port = 8080; 
    //server Address information
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    // serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");         //binds only to localhost
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);              //binds to all available interfaces
    serverAddress.sin_port = htons(port);

    //Assign socket address to declared socket
    int fails=bind(serverFileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)); 
    if(fails){
        fprintf(stderr,"Couldn't bind to the port: %d\n",port);
        return;
    }

    //Start listening on the port, maximum allowed clients is 5
    fails=listen(serverFileDescriptor,5); 
    if(!fails){
        cout<<"Listening...\n";
    }

    clientFileDescriptor = accept(serverFileDescriptor,NULL,NULL);
    cout<<"Client connected\n";
}

void client_wait(){
    int socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    FILE* socketRead = fdopen(socketFileDescriptor,"r+"); 
    if(socketFileDescriptor<0){
        cout<<"Couldn't create socket\n";
        return;
    }
    int port = 8080;
    //Server address information
    struct sockaddr_in serverAddress; 
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(port); 

    // Connect to server
    int status= connect(socketFileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    cout<<"Connected to server\n";
}

void send_initial_values(){
    cout<<"serverFileDescriptor: "<<serverFileDescriptor<<" clientFileDescriptor: " <<
    clientFileDescriptor <<endl;
    // int data_sent = send(clientFileDescriptor,recv_initial_values,SEND_SIZE,0);
    // cout<<"Data sent:"<<data_sent<<endl;
}

void recv_initial_values(){
    
}