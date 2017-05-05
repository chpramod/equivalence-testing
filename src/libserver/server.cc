#include "server.h"

int serverFileDescriptor;
int clientFileDescriptor;

void store_input(struct INPUT* in){
    FILE* fp = fopen("server_input","w");
    // in->inputs[in->num*sizeof(value_t)]='\0';
    int a;
    // char buf[4];
    // memcpy(buf,&in->num,sizeof(int));
    a = fprintf(fp,"%d\n",in->num);
    // printf("!!%d",a);
    for(int i=0;i<in->num;i++){
        a = fprintf(fp,"%lld\n",in->inputs[i]);
        // printf("!!%d",a);
    }
    fclose(fp);
}

FDS socket_pair(int port){
    int opt = TRUE;
    int master_socket , addrlen , new_socket , client_socket[3] , max_clients = 3, activity, i , valread , sd;
    int max_sd;
    struct sockaddr_in address;
    FDS fds;
      
    char buffer[1025];  //data buffer of 1K
      
    //set of socket descriptors
    fd_set readfds;
      
    //a message
    char *message = "ECHO Daemon v1.0 \r\n";
  
    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++) 
    {
        client_socket[i] = 0;
    }
      
    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
  
    //set master socket to allow multiple connections , this is just a good habit, it will work without this
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
  
    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
      
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0) 
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", port);
     
    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 10) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
      
    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    FD_ZERO(&readfds);
  
    //add master socket to set
    FD_SET(master_socket, &readfds);
    max_sd = master_socket;
    for(int i=0;i<max_clients;i++){
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR)) {
                // printf("select error\n");
                exit(0);
        }

        if (FD_ISSET(master_socket, &readfds)) {
            printf("Activity on master => Incoming\n");
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
                perror("accept");
                exit(EXIT_FAILURE);
            }
              
                //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d master: %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port), master_socket);
            
                //send new connection greeting message
                // if( send(new_socket, message, strlen(message), 0) != strlen(message) ) 
                // {
                //     perror("send");
                // }
                  
                // puts("Welcome message sent successfully");
                  
                //add new socket to array of sockets
            client_socket[i] = new_socket;
            fds.fd[i] = new_socket;
            max_sd ++;
        }
    }
    fds.max_clients = max_clients;
    fds.readfds = readfds;
    fds.master_socket = master_socket;
    for(int i=0;i<max_clients;i++){
        fds.available[i] = 1;
    }
    return fds;
    // serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    // if(serverFileDescriptor<0){
    //     // cout<<"Couldn't create socket\n";
    //     return;
    // }
    // // printf("serverFileDescriptor: %d\n",serverFileDescriptor);
    // // int port = 8080; 
    // //server Address information
    // struct sockaddr_in serverAddress;
    // serverAddress.sin_family = AF_INET;
    // // serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");         //binds only to localhost
    // serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);              //binds to all available interfaces
    // serverAddress.sin_port = htons(port);

    // //Assign socket address to declared socket
    // int fails=bind(serverFileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)); 
    // if(fails){
    //     fprintf(stderr,"Couldn't bind to the port: %d, Exiting..\n",port);
    //     exit(0);
    //     return;
    // }
    // //Start listening on the port, maximum allowed clients is 5
    // fails=listen(serverFileDescriptor,5); 
    // if(!fails){
    //     printf("Listening...\n");
    // }

    // clientFileDescriptor = accept(serverFileDescriptor,NULL,NULL);
    // // printf("clientFileDescriptor: %d\n",clientFileDescriptor);
    // FILE *fp = fopen("client_fd","w");
    // fwrite((void *)&clientFileDescriptor,sizeof(int),1,fp);
    // fclose(fp);
    // printf("Client connected\n");
}

FDS client_wait(int port){
    int socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    // printf("serverFileDescriptor: %d\n",socketFileDescriptor);
    // FILE *fp = fopen("server_fd","w");
    // fwrite((void *)&socketFileDescriptor,sizeof(int),1,fp);
    // fclose(fp);
    // FILE* socketRead = fdopen(socketFileDescriptor,"r+"); 
    if(socketFileDescriptor<0){
        printf("Couldn't create socket\n");
        exit(0);
    }
    FDS serverFDS;
    serverFDS.fd[0] = socketFileDescriptor; 
    // int port = 8080;
    //Server address information
    struct sockaddr_in serverAddress; 
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(port); 

    // Connect to server
    int status= connect(socketFileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    //cout<<"Connected to server\n";
    return serverFDS;
}

void send_initial_values(int sockid,char buf[], int len){    
    int data_sent = send(sockid,buf,len,0);
    // printf("Data sent %d\n",data_sent);
    // cout<<"Data sent:"<<data_sent<<endl;
}

void send_branch_cond_first(FDS* fds,char* s, int len){
    int data_sent = send(fds->fd[0],s,len,0);
    // printf("send_branch_cond %d\n",data_sent);
    fds->available[0] = 0;
    fd_set readfds = fds->readfds;
    /*int master_socket = fds.master_socket;
    int max_clients = max_clients;
    FD_ZERO(&readfds);  
        //add master socket to set
    FD_SET(master_socket, &readfds);
    int max_sd = master_socket;
    int sd;   
    char buffer[1025];  //data buffer of 1K
        //add child sockets to set
    int i;
    for ( i = 0 ; i < max_clients ; i++) 
    {
        //socket descriptor
        sd = fds.fd[i];
         
        //if valid socket descriptor then add to read list
        if(sd > 0)
            FD_SET( sd , &readfds);
         
        //highest file descriptor number, need it for the select function
        if(sd > max_sd)
            max_sd = sd;
    }
        printf("Before Select\n");
        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
    // int activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
    //     // printf("After Select\n");
    
    // if ((activity < 0) && (errno!=EINTR)) 
    // {
    //     printf("select error");
    // }
    int valread;
    for (i = 0; i < max_clients; i++) 
    {
        sd = fds.fd[i];
        if (FD_ISSET( sd , &readfds)) 
        {
            //Check if it was for closing , and also read the incoming message
            if ((valread = read( sd , buffer, 1024)) <= 0)
            {
                //Somebody disconnected , get his details and print
                // getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                // printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                  printf("Client disconnected");
                //Close the socket and mark as 0 in list for reuse
                close( sd );
                fds.fd[i] = 0;
            }
              
            //Echo back the message that came in
            else
            {
                //set the string terminating NULL byte on the end of the data read
                buffer[valread] = '\0';
                printf("Received from one client : %s\n",buffer );
                if(strcmp(buffer,"Matched")==0){
                    fds.available[i] = 1;
                }else{
                    printf("Programs are not similar\n");
                    exit(0);
                }
                // printf("SEND : %d\n",sd);
                // send(sd , buffer , strlen(buffer) , 0 );
            }
        }
    }
    
    for(i=0;i<max_clients;i++){
        if(fds.available[i]==1){
            int data_sent = send(fds.fd[i],s,len,0);
            printf("send_branch_cond %d\n",data_sent);
            fds.available[i] = 0;
            break;
        }
    }
    }  */  
}

void send_branch_cond(FDS* fds,char* s, int len){
    fd_set readfds = fds->readfds;
    int master_socket = fds->master_socket;
    int max_clients = fds->max_clients;
    
    for(int i=0;i<max_clients;i++){
        if(fds->available[i]==1){
            int data_sent = send(fds->fd[i],s,len,0);
            // printf("send_branch_cond %d\n",data_sent);
            fds->available[i] = 0;
            return;
        }
    }
    FD_ZERO(&readfds);  
        //add master socket to set
    FD_SET(master_socket, &readfds);
    int max_sd = master_socket;
    int sd;   
    char buffer[1025];  //data buffer of 1K
        //add child sockets to set
    int i;
    for ( i = 0 ; i < max_clients ; i++) 
    {
        //socket descriptor
        sd = fds->fd[i];
         
        //if valid socket descriptor then add to read list
        if(sd > 0)
            FD_SET( sd , &readfds);
         
        //highest file descriptor number, need it for the select function
        if(sd > max_sd)
            max_sd = sd;
    }
        // printf("Before Select\n");
        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
    int activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
        // printf("After Select\n");
    
    if ((activity < 0) && (errno!=EINTR)) 
    {
        // printf("select error");
        exit(0);
    }
    int valread;
    for (i = 0; i < max_clients; i++) 
    {
        sd = fds->fd[i];
        if (FD_ISSET( sd , &readfds)) 
        {
            //Check if it was for closing , and also read the incoming message
            if ((valread = read( sd , buffer, 1024)) <= 0)
            {
                //Somebody disconnected , get his details and print
                // getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                // printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                  printf("Client disconnected");
                //Close the socket and mark as 0 in list for reuse
                close( sd );
                fds->fd[i] = 0;
            }
              
            //Echo back the message that came in
            else
            {
                //set the string terminating NULL byte on the end of the data read
                buffer[valread] = '\0';
                printf("Received from one client : %s\n",buffer );
                if(strcmp(buffer,"Matched")==0){
                    fds->available[i] = 1;
                }else{
                    printf("Programs are not similar\n");
                    exit(0);
                }
                // printf("SEND : %d\n",sd);
                // send(sd , buffer , strlen(buffer) , 0 );
                /* Enter into list */

            }
        }
    }

    /* If list empty then wait else send */
    
    
}

int recv_constraints(int sockid, char *s){
    bzero(s,1024);
    int dataRec = 0;
    // printf("Waiting for constraints\n");
    while (dataRec==0)
        dataRec = recv(sockid,s,1024,0);
    if(dataRec < 0)
        exit(0);
    // printf("New:%d\n",s);
    // char server_constraints[dataRec];
    // bzero(server_constraints,dataRec);
    // memcpy(server_constraints,s,dataRec);
    // istringstream iss(server_constraints);
    // size_t len;
    // iss.read((char*)&len, sizeof(size_t));
    // printf("Server.cc recv_constraints len:%d\n",len );
    // printf("Constraints Received : %d\n",dataRec);
    return dataRec;
}


int recv_ans(int sockid){
    char buf[10];
    bzero(buf,10);
    int data_recv = recv(sockid,buf,10,0);
    int ans = *(int *)buf; 
    // printf("Ans recv:%d %d\n",ans,data_recv);
    if(ans == 1){
        return 1;
    }else{
        return 0;
    }
}

int send_ans(char *a1, char *a2, int len1, int len2){
    int ans = 1;
    printf("%s\n%s\n",a1,a2);
    printf("len1:%d len2:%d\n",len1,len2);
    if(len1 != len2){
        return 0;
    }
    // printf("%d %d\n",strlen(a1),strlen(a2));
    if(strncmp(a1,a2,len1)!=0)
        ans = 0;
    return ans;
}

int match_outputs(int sockid, char output_server[]){
    char buf[1024];
    bzero(buf,1024);
    int data_recv = recv(sockid,buf,1024,0);
    if(strcmp(buf,output_server)==0){
        return 1;
    }else{
        return 0;
    }
}

void send_output(FDS fds,char buf[],int len){
    int data_sent = send(fds.fd[0],buf,len,0);
    // printf("send_output %d\n",data_sent);
}

void can_die(FDS fds){
    int max_clients = fds.max_clients;
    fd_set readfds = fds.readfds;
    char buffer[1025];
    int max_sd = fds.master_socket;
    while(1){
        int active = 0;
        for(int i=0;i<max_clients;i++){
            if(fds.available[i] == 1)
                active ++;
        }
        if(active == max_clients){
            printf("Job finished\n");
            return;
        }
        int i;
        int sd;
        for ( i = 0 ; i < max_clients ; i++) 
        {
            //socket descriptor
            sd = fds.fd[i];
             
            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);
             
            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }
        // printf("Before Select\n");
        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        int activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
        // printf("After Select\n");
    
        if ((activity < 0) && (errno!=EINTR)) 
        {
            // printf("select error");
            exit(0);
        }
        int valread;
        for (i = 0; i < max_clients; i++) 
        {
            sd = fds.fd[i];
            if (FD_ISSET( sd , &readfds)) 
            {
                //Check if it was for closing , and also read the incoming message
                if ((valread = read( sd , buffer, 1024)) <= 0)
                {
                    //Somebody disconnected , get his details and print
                    // getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    // printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                      printf("Client disconnected");
                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    fds.fd[i] = 0;
                }
                  
                //Echo back the message that came in
                else
                {
                    //set the string terminating NULL byte on the end of the data read
                    buffer[valread] = '\0';
                    printf("Received from one client : %s\n",buffer );
                    if(strcmp(buffer,"Matched")==0){
                        fds.available[i] = 1;
                    }else{
                        printf("Programs are not similar\n");
                        exit(0);
                    }
                    // printf("SEND : %d\n",sd);
                    // send(sd , buffer , strlen(buffer) , 0 );
                    /* Enter into list */

                }
            }
        }
    }
}

void recv_output(int sockid, char output_server[]){
    int data_recv = recv(sockid,output_server,1024,0);
    printf("sockid:%d\n",sockid);
    if(data_recv == -1){
        printf("%d\n",EIO);
        printf("%d\n",EAGAIN);
        printf("%d\n",EBADF);
        printf("%d\n",ECONNRESET);
        // printf("%d\n",ETIMEDOUT);
        printf("%d\n",ENOBUFS);
        printf("%d\n",EINTR);
        printf("%d\n",EINVAL);
        // printf("%d\n",EISCONN);
        // printf("%d\n",EMSGSIZE);
        // printf("%d\n",ENOBUFS);
        printf("%d\n",ENOMEM);
        printf("%d\n",ENOTCONN);
        printf("%d\n",ENOTSOCK);
        printf("%d\n",ETIMEDOUT);
        printf("%d\n",EOPNOTSUPP);
        printf("%d\n",errno);
    }
    printf("recv_output %d\n",data_recv);
}

// if(data_sent == -1){
        // printf("sockid:%d\n",sockid);
        // printf("%d\n",EACCES);
        // printf("%d\n",EAGAIN);
        // printf("%d\n",EBADF);
        // printf("%d\n",ECONNRESET);
        // printf("%d\n",EDESTADDRREQ);
        // printf("%d\n",EFAULT);
        // printf("%d\n",EINTR);
        // printf("%d\n",EINVAL);
        // printf("%d\n",EISCONN);
        // printf("%d\n",EMSGSIZE);
        // printf("%d\n",ENOBUFS);
        // printf("%d\n",ENOMEM);
        // printf("%d\n",ENOTCONN);
        // printf("%d\n",ENOTSOCK);
        // printf("%d\n",EPIPE);
        // printf("%d\n",EOPNOTSUPP);
        // printf("%d\n",errno);
    // }