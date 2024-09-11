#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>

#define PORTNO 10678

int main(){
     char buff[100], str[100];

    int socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_id == -1){
        perror("Socket creation failed.\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("0.0.0.0");
    address.sin_port = htons(PORTNO);

    connect(socket_id, (struct sockaddr *)&address, sizeof(address));

    printf("Enter string: ");
    scanf("%s",str);

    write(socket_id, str, sizeof(str));

    sleep(2);

    printf("\nReading servers' response...");
    read(socket_id, buff, sizeof(buff));
    printf("%s\n",buff);
    close(socket_id);
}