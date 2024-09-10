// TCP code to find transpose of a matrix

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>

#define PORTNO 10892

int main(){
    int arr[3][3], buff[3][3];
    int socket_id = socket(AF_INET, SOCK_DGRAM, 0);

    if(socket_id == -1){
        perror("Couldn't create socket...\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);

    printf("Enter array: ");
    for(int i = 0; i < 3; i++){
        for(int j = 0 ; j < 3; j++){
            scanf("%d", &arr[i][j]);
        }
    }
    printf("Sending array to server...\n");

    // UDP send to server
    sendto(socket_id, &arr, sizeof(arr), 0, (struct sockaddr *)&address, sizeof(address));

    // socklen here

    socklen_t lenn = sizeof(address);
    recvfrom(socket_id, buff, sizeof(buff), 0, (struct sockaddr *)&address, &lenn);

    printf("Received array from server:\n");
    for(int i = 0; i < 3; i++){
        for(int j = 0 ; j < 3; j++){
            printf("%d ", buff[i][j]);
        }
        printf("\n");
    }

    close(socket_id);
