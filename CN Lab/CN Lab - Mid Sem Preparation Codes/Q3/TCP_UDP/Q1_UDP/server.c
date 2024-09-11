#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>

#define PORTNO 12653

int main(){
    int socket_id = socket(AF_INET, SOCK_DGRAM, 0);

    char buff[100], str[100];

    struct sockaddr_in serveraddress;
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = inet_addr("0.0.0.0");
    serveraddress.sin_port = htons(PORTNO);

    struct sockaddr_in clientaddress;
    socklen_t clilen = sizeof(clientaddress);

    bind(socket_id, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
    printf("Server is waiting...\n");

    recvfrom(socket_id, buff, sizeof(buff), 0, (struct sockaddr *)&clientaddress, &clilen);

    int lenstr = strlen(buff);
        for(int i = 0; i < lenstr; i++){
            str[i] = buff[lenstr - i - 1];
        }
        str[lenstr] = '\0';

    sendto(socket_id, str, sizeof(str), 0, (struct sockaddr *)&clientaddress, clilen);
    close(socket_id);
}