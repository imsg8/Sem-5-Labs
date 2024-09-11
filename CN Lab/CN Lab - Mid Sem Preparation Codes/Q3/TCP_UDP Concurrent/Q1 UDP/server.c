#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>

#define PORTNO 15674

int main(){
    printf("Server running...\n");

    int socket_id = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in clientaddress;
    socklen_t clilen = sizeof(clientaddress);
    if(socket_id == -1){
        perror("Socket creation failed at server's end.\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serveraddress;
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = inet_addr("0.0.0.0");
    serveraddress.sin_port = htons(PORTNO);

    bind(socket_id, (struct sockaddr *)&serveraddress, sizeof(serveraddress));

    while(1){
        char buff[100], str[100];

        recvfrom(socket_id, buff, sizeof(buff), 0, (struct sockaddr *)&clientaddress, &clilen);

        if (fork() == 0) {  // Fork a new process to handle the client
            int lenstr = strlen(buff);
            for(int i = 0; i < lenstr; i++){
                str[i] = buff[lenstr - i - 1];
            }
            str[lenstr] = '\0';

            sendto(socket_id, str, strlen(str) + 1, 0, (struct sockaddr *)&clientaddress, clilen);
            exit(0);  // Child process exits after handling the request
        }
    }

    close(socket_id);
}
