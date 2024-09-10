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

    printf("Server running...\n");

    int socket_id = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_id == -1){
        perror("Socket not created...\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORTNO);

    if (bind(socket_id, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed...\n");
        exit(EXIT_FAILURE);
    }

    socklen_t client_len = sizeof(client_address);

    while(1){
        printf("Waiting for client data...\n");

        recvfrom(socket_id, &arr, sizeof(arr), 0, (struct sockaddr*)&client_address, &client_len);

        printf("Data received, processing...\n");

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                buff[i][j] = arr[j][i];
            }
        }

        sendto(socket_id, &buff, sizeof(buff), 0, (struct sockaddr*)&client_address, client_len);

        printf("Processed data sent back to client.\n");
    }

    // Close the socket after the server is done (outside the loop)
    close(socket_id);
    return 0;
}
