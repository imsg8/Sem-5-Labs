#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORTNO 10340

struct client_data{
     char name[100];
    long int regno;
    int gpa[4];
};

struct server_data{
    char name[100];
    int cgpa;
    char grade;
};

int main(){
    printf("Server running...\n");

    struct client_data cli;
    struct server_data ser;
    float avg = 0; 

    int socket_id = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_id == -1){
        perror("Error in socket...\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serveraddress;
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = inet_addr("0.0.0.0");
    serveraddress.sin_port = htons(PORTNO);

    bind(socket_id, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
    listen(socket_id, 5);

    while(1){
        struct sockaddr_in clientaddress;
        socklen_t clilen = sizeof(clientaddress);

        // YAHA GAME HUA THA (ERROR)
        int new_socket_id = accept(socket_id, (struct sockaddr *)&clientaddress, &clilen);

        read(new_socket_id, &cli, sizeof(struct client_data));
        printf("\nClient data for %s with reg no %ld has arrived.\n", cli.name, cli.regno);
        for (int i = 0; i < 4; i++){
            avg += cli.gpa[i];
        }
        avg = avg/4;
        ser.cgpa = avg;
        strcpy(ser.name, cli.name);
        if(avg > 8){
            ser.grade = 'A';
        }
        else if(avg > 5 && avg < 7.5){
            ser.grade = 'B';
        }
        else{
            ser.grade = 'C';
        }
        write(new_socket_id, &ser, sizeof(struct server_data));
        close(new_socket_id);
    }
    close(socket_id);
}