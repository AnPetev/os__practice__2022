#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUF_SIZE 1024
#define LENGTH 2048
#define NULL
int flag = 0;
int sockfd = 0;

//Receive message//
void receive_message() {
	char message[LENGTH] = {};
  while (1) {
		int receive = recv(sockfd, message, LENGTH, 0);
    if (receive > 0) {
      printf("%s", message);
      printf("%s", "> ");
      fflush(stdout);
    } 
    else if (receive == 0){
			break;
    }
	memset(message, 0, sizeof(message));
  }
}

//Send message//
void send_message() {
  char message[LENGTH] = {};
  char buffer[LENGTH + 32] = {};
  char* name[16];

  while(1) {
  	printf("%s", "> ");
    fgets(message, LENGTH, stdin);
    if (strcmp(message, "exit") == 0) {
			break;
    } else {
      sprintf(buffer, "%s: %s\n", name, message);
      send(sockfd, buffer, strlen(buffer), 0);
    }
  }
}

int main(int argc, char** argv) {  
    struct sockaddr_in adress;  
    int sockfd, ret;  
    char buffer[BUF_SIZE]; 
    char* server_adress;
    pthread_t thread;

    if (argc < 2) {
        printf("usage: client < ip address >\n");
     exit(1);  
 }
 server_adress = argv[1]; 

 //Creating socket//
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  
    if (sockfd < 0) {  
        printf("Error creating socket!\n");  
    exit(1);  
 }  
    short int port = 8888;
    printf("Socket created...\n");   
    memset(&adress, 0, sizeof(adress));  
    adress.sin_family = AF_INET;  
    adress.sin_addr.s_addr = inet_addr(server_adress);
    adress.sin_port = htons(port);   
    
 //Connecting to the server//
    ret = connect(sockfd, (struct sockaddr *) &adress, sizeof(adress));  
    if (ret < 0) {  
      printf("Error connecting to the server!\n");  
    exit(1);  
  }  
    printf("Connected to the server...\n");  

    memset(buffer, 0, BUF_SIZE);
    printf("Enter your messages\n");
    pthread_t send_msg_thread;

    if(pthread_create(&send_msg_thread, NULL, (void *) send_message, NULL) != 0){
		printf("ERROR: pthread\n");
    return EXIT_FAILURE;
	}

	pthread_t recv_msg_thread;
      if(pthread_create(&recv_msg_thread, NULL, (void *) receive_message, NULL) != 0){
		printf("ERROR: pthread\n");
		return EXIT_FAILURE;
	}

    while (1){
	  if(flag){
		printf("exit");
		break;
    }
	}
	close(sockfd);

	return EXIT_SUCCESS;
}
