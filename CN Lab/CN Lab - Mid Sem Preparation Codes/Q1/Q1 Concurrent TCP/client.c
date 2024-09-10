// TCP code to find transpose of a matrix

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

    int socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_id == -1){
        perror("Socket not created...\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);

    connect(socket_id, (struct sockaddr*)&address, sizeof(address));

    printf("Enter array: ");
    for(int i = 0; i < 3; i++){
        for(int j = 0 ; j < 3; j++){
            scanf("%d", &arr[i][j]);
        }
    }
    printf("Sending array to server...\n");

    write(socket_id, &arr, sizeof(arr));
    read(socket_id, buff, sizeof(buff));

    printf("Recieved array from server:\n");
    for(int i = 0; i < 3; i++){
            for(int j = 0 ; j < 3; j++){
                printf("%d\t", buff[i][j]);
            }
            printf("\n");
        }
}
