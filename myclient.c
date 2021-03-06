#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

void * doRecieving(void * sockID){

	int clientSocket = *((int *) sockID);

	while(1){

		char data[1024];
		int read = recv(clientSocket,data,1024,0);
		data[read] = '\0';
		printf("%s\n",data);

	}

}

int main(int argc,char *argv[]){

	int portno;
	char username[100];

	if(argc > 3) {
		printf("too many arguments");
		exit(1);
	}
	portno = atoi(argv[2]);
	strcpy(username,argv[1]);

	int clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(portno);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) return 0;

	printf("Connection established ............\n");
	
	send(clientSocket,username,1024,0);

	pthread_t thread;
	pthread_create(&thread, NULL, doRecieving, (void *) &clientSocket );

	while(1){

		char input[1024];
		scanf("%s",input);

/*		if(strcmp(input,"LIST") == 0){

			send(clientSocket,input,1024,0);

		}
*/
		if(strcmp(input,"send") == 0){

			send(clientSocket,input,1024,0);
			
			scanf("%s",input);
			send(clientSocket,input,1024,0);

			fflush(stdin);
			
			scanf("%[^\n]s",input);
			send(clientSocket,input,1024,0);

		}
		if(strcmp(input,"sendgroup") == 0){

			send(clientSocket,input,1024,0);
			
			scanf("%s",input);
			send(clientSocket,input,1024,0);

			fflush(stdin);

			scanf("%[^\n]s",input);
			send(clientSocket,input,1024,0);

		}
		if(strcmp(input,"creategroup") == 0){

			send(clientSocket,input,1024,0);
			
			scanf("%s",input);
			send(clientSocket,input,1024,0);
			
			scanf("%s",input);
			send(clientSocket,input,1024,0);

			int p=atoi(input);
			for( int i=0;i<p;i++)
			{
			scanf("%s",input);
			//printf("n=%d",atoi(input));			
			send(clientSocket,input,1024,0);
			}
		}
	}
}
