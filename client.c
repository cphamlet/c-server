// Write CPP code here 
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "commbuf.h"

#define PORT 8080 
#define SA struct sockaddr 
void func(int sockfd, struct CommunicationBuffer *commBuf) 
{ 

	int n; 
	for (;;) { 
		bzero(commBuf->buffer, commBuf->size); 
		printf("Enter the string: "); 
		n = 0; 
		while (n<commBuf->size && (commBuf->buffer[n++] = getchar()) != '\n') 
			; 

        printf("ABOUT TO EXECUTE WRITE: %s \n ", commBuf->buffer);
		write(sockfd, commBuf->buffer, commBuf->size); 
        printf("WROTE TO SOCKET\n");
		bzero(commBuf->buffer, commBuf->size); 
		read(sockfd, commBuf->buffer, commBuf->size); 
		printf("From Server : %s", commBuf->buffer); 
		if ((strncmp(commBuf->buffer, "exit", 4)) == 0) { 
			printf("Client Exit...\n"); 
			break; 
		} 
	} 
} 

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 
    struct CommunicationBuffer commBuf = {.size=80, .buffer=0};
    allocateCommunicationBuffer(&commBuf);

	// socket create and varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	else
		printf("connected to the server..\n"); 

	// function for chat 
	func(sockfd, &commBuf); 

	// close the socket 
	close(sockfd); 
} 
