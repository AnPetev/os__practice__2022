#include <stdio.h>
#include <string.h>   
#include <errno.h>
#include <arpa/inet.h>    
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> 
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_CLIENTS 128
#define BUFFER_SIZE 2048

static int uid = 10;
unsigned int client_count = 0;

typedef struct{
	struct sockaddr_in address;
	int sockfd;
	int uid;
	char name[32];
} client_t;

client_t *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex;
//Add clients to queue//
void queue_add(client_t *client){
	pthread_mutex_lock(&clients_mutex);
	for(int i=0; i < MAX_CLIENTS; ++i){
		if(!clients[i]){
			clients[i] = client;
			break;
		}
	}
	pthread_mutex_unlock(&clients_mutex);
}

//Send message to all clients//
void send_message(char *s, int uid){
	pthread_mutex_lock(&clients_mutex);
	for(int i=0; i<MAX_CLIENTS; ++i){
		if(clients[i]){
			if(clients[i]->uid != uid){
				if(write(clients[i]->sockfd, s, strlen(s)) < 0){
					perror("ERROR: ");
					break;
				}
			}
		}
	}
	pthread_mutex_unlock(&clients_mutex);
}

//Deal with client//
void deal_with_client(void *arg){
	char buffer[BUFFER_SIZE];
	char name[32];
	int  flag = 0;
	client_count++;
	client_t *client = (client_t *)arg;
	}

int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage",argv[0]);
		return EXIT_FAILURE;
	}

	char *ip = "127.0.0.1";
	int port = 8888;
	int option = 1;
	int listenfd = 0, connfd = 0;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    pthread_t thread;

  //Socket//
   listenfd = socket(AF_INET, SOCK_STREAM, 0);
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = inet_addr(ip);
   server_addr.sin_port = htons(port);

    if(bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("ERROR: Socket binding failed");
    return EXIT_FAILURE;
  }

  //Listen//
  if (listen(listenfd, 10) < 0) {
     perror("ERROR: Socket listening failed");
     return EXIT_FAILURE;
	}
	 printf("Welcome to the chatroom");

	while(1){
		socklen_t clilen = sizeof(client_addr);
		connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client);

		//Check if max client counts is reached//
	if((client_count + 1) == MAX_CLIENTS){
		printf("Max clients reached. Rejected: ");
		print_client_addr(client_addr);
		printf(":%d\n", client_addr.sin_port);
		close(connfd);
		continue;
		}
 
		client_t *client = (client_t *)malloc(sizeof(client_t));
		client->address = client_addr;
		client->sockfd = connfd;
		client->uid = uid++;

		//Add client to the queue and fork thread //
		queue_add(client);
		pthread_create(&thread, NULL, &deal_with_client, (void*)client);

		sleep(1);
	}

	return EXIT_SUCCESS;
}
