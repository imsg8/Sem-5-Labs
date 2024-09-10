#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>

#define PORTNO 10478

int main(){
    int arr[3][3], buff[3][3];

    printf("Server running...\n");

    int socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_id == -1){
        perror("Socket not created...\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serveraddress;
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddress.sin_port = htons(PORTNO);

    bind(socket_id, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
    listen(socket_id, 5);

    while(1){
        struct sockaddr_in clientaddress;
        socklen_t clilen= sizeof(clientaddress);
        int new_socket_id = accept(socket_id, (struct sockaddr *)&clientaddress, &clilen);

        read(new_socket_id, arr, sizeof(arr));

        for(int i = 0; i < 3; i++){
            for(int j = 0 ; j < 3; j++){
                buff[i][j] = arr[j][i];
            }
        }

        write(new_socket_id, buff, sizeof(buff));
        close(new_socket_id);
    }
    close(socket_id);
