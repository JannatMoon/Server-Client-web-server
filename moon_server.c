#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<pthread.h>
#define PORT 8080 

char buffer[1024] = {0};
int server_fd, new_socket, valread , *n_s;  

void th ();

int main(int argc, char const *argv[]) 
{ 
    //int server_fd, new_socket, valread , *n_s; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    //char buffer[1024] = {0}; 
    //char *hello = "Hello from server"; 
    pid_t n;
    //pthread_t thread;
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 



    
    
while(new_socket = accept(server_fd, (struct sockaddr *)&address,  (socklen_t*)&addrlen)){
	//pthread_create(&thread , NULL , th , NULL);
	
    pthread_t thread;
    n_s = malloc(1);
    *n_s = new_socket;
    pthread_create(&thread , NULL , th , (void*) n_s);
    
    }

    
    return 0; 
}


void th ()
{
	
	char *hello = "Hello from server"; 
	
	
	while((valread = read( new_socket , buffer, 1024)) > 0)
	{
	
	 if(strcmp(buffer, "exit") == 0){
			printf("server Disconnected\n");
			break;
		}
	
	  printf("%s\n",buffer);
	  send(new_socket , hello , strlen(hello)+1 , 0 );
	}
	
	
	//free(fd_pointer) ;
	
	return 0;
}



