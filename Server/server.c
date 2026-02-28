#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#define MESSAGE_MAX 80 
#define PORT 8080 
#define NAME_LENGTH 12
#define MAX_CLIENTS 5
#define SA struct sockaddr 

void chat(int connfd)
{
	char username[NAME_LENGTH];
	char message[MESSAGE_MAX];
	int n = read(connfd, username, sizeof(username));
	if (n>0){
		username[n] = '\0';
		printf("%s Connected.\n", username);
	}
	for (;;) {
                n = read(connfd, message, sizeof(message));
                printf("%s: %s \n", username, message);
             	if (n > 0){
			message[n] = '\0';
		}else if (n == 0){
			printf("%s disconnected", username);
			break;
		}else
			printf("Read failed");
                fgets(message, MESSAGE_MAX, stdin);
		message[strcspn(message, "\n")] = '\0';
                write(connfd, message, sizeof(message));

                if (strncmp("exit", message, 4) == 0){
                        printf("Server Exit\n");
                        break;
                }
        }
}

int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Socket creation Failed\n");
		exit(0);
	}
	else
		printf("Socket succesfully created\n");
	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0){
		printf("Socket bind failed\n");
		exit(0);
	}
	else
		printf("Socket successfully binded\n");
	if ((listen(sockfd, 5)) !=0){
		printf("listen failed\n");
		exit(0);
	}
	else
		printf("Server listening on \n");
	len = sizeof(cli);
	
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd <0){
		printf("Server Accept failed\n");
		exit(0);
	}
	else
		printf("Server accepted client\n");
	chat(connfd);

	close(sockfd);

}
