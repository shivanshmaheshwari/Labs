#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define SIZE 1024

void sendFile(char *filename, int sockfd) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("[-]Error reading list.");
        exit(1);
    }
    // File transfer:
    char data[SIZE] = {0};
    while(fgets(data, SIZE, fp) != NULL) {
        if(send(sockfd, data, sizeof(data), 0) == -1) {
            perror("[-]Error in sending file.");
            exit(1);
        }
        bzero(data, SIZE);
    }
    fclose(fp);
}

int main() {
    // Create socket:
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        printf("Socket Creation FAILED!!\n");
        exit(1);
    }
    printf("Socket created successfully\n");

    // Set port and IP:
    struct sockaddr_in servaddr, cliaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(2080);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind to the set port and IP:
    if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("Bind Failed!!\n");
        exit(1);
    }
    printf("Bind Successfull!!\n");

    // Listen for clients:
    if(listen(sockfd, 1) < 0){
        printf("Error, Couldnt Listen !!\n");
        exit(1);
    }
    printf("\nListening for incoming client messages..\n");

    // Accept an incoming connection:
    int client_size = sizeof(cliaddr);
    int client_sock = accept(sockfd, (struct sockaddr*)&cliaddr, &client_size);

    if (client_sock < 0){
        printf("Can't accept the message\n");
        exit(1);
    }
    printf("Client connected at IP: %s and port: %i\n",
        inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

    system("ls >> list"); 
    sendFile("list", client_sock);
    // system("rm list");
    printf("List sent successfully.\n");

    // char filename[SIZE];
    // recv(client_sock, filename, SIZE, 0);
    // printf("File requested: %s\n", filename);

    // sendFile(filename, client_sock);
    // printf("File sent successfully.\n");

    // Closing the socket:
    close(client_sock);
    close(sockfd);
    return 0;
}