#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#define NAME_LENGTH 12
#define MESSAGE_MAX 80
#define PORT 8080
#define SA struct sockaddr

void chat(int sockfd){
	char username[NAME_LENGTH];
	int n = 0;
	printf("Enter User name.\n");
	memset (username, 0, NAME_LENGTH);
	fgets(username, NAME_LENGTH, stdin);
	username[strcspn(username, "\n")] = '\0';
	write(sockfd, username, sizeof(username));
	char message[MESSAGE_MAX];
	for (;;){
		printf("Enter message: ");
		n=0;
		fgets(message, MESSAGE_MAX, stdin);
		message[strcspn(message, "\n")] = '\0';
		write(sockfd, message, sizeof(message));

		
		read(sockfd, message, sizeof(message));
		printf("From Server:  %s", message);

		if (strncmp("exit", message, 4) == 0){
			printf("Client Exit\n");
			break;
		}
	}
}

int main(){
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd ==-1){
		printf("Socket creation failed\n");
		exit(0);
	}
	else
		printf("Socket successfully created\n");
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0){
		printf("Connection with the server failed\n");
		exit(0);
	}
	else
		printf("Succcesfully connected to the server\n");
	chat(sockfd);

	close(sockfd);
}
