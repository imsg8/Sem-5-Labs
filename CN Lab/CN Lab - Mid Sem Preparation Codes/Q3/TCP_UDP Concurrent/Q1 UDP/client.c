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
    char buff[100], str[100];

    int socket_id = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_id == -1){
        perror("Client running...\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("0.0.0.0");
    address.sin_port = htons(PORTNO);

    printf("Enter string: ");
    scanf("%s",str);
    printf("Sending to server...\n");
    socklen_t len1 = sizeof(address);
    sendto(socket_id, str, sizeof(str), 0, (struct sockaddr *)&address, len1);
    recvfrom(socket_id, buff, sizeof(buff), 0, (struct sockaddr *)&address, &len1);
    printf("Recieved string is: %s\n", buff);
    close(socket_id);
}