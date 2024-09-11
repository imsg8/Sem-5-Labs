#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>

#define PORTNO 15643

int main(){
    printf("Server running...\n");
    int socket_id = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_id == -1){
        perror("Socket creations failed at servers end.\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serveraddress;
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = inet_addr("0.0.0.0");
    serveraddress.sin_port = htons(PORTNO);

    bind(socket_id, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
    listen(socket_id, 5);

    while(1){
        char buff[100], str[100];
        struct sockaddr_in clientaddress;
        socklen_t clilen = sizeof(clientaddress);
        int new_socket_id = accept(socket_id, (struct sockaddr *)&clientaddress, &clilen);

        read(new_socket_id, buff, sizeof(buff));

        int lenstr = strlen(buff);
        for(int i = 0; i < lenstr; i++){
            str[i] = buff[lenstr - i - 1];
        }
        str[lenstr] = '\0';

        write(new_socket_id, str, sizeof(str));
        close(new_socket_id);
    }
    close(socket_id);
}