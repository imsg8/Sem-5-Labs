// PLAYING WITH STRUCTURES IN CLIENT-SERVER TCP

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

    char buffer[256];
    int socket_id = socket(AF_INET, SOCK_STREAM, 0);

    struct client_data cli;
    struct server_data ser;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("0.0.0.0");
    address.sin_port = htons(PORTNO);

    connect(socket_id, (struct sockaddr *)&address, sizeof(address));

    printf("Enter the name of the student: ");
    scanf("%s", cli.name);
    printf("\nEnter reg no of %s: ",cli.name);
    scanf("%ld",&cli.regno);
    printf("\nEnter GPAs of last 4 semesters: ");
    for(int i = 0; i < 4; i++){
        printf("Enter for semester %d: ", i + 1);
        scanf("%d",&cli.gpa[i]);
        printf("\n");
    }
    
    printf("\nStudent is %s and reg no is %ld, sending to server...\n",cli.name, cli.regno);
    write(socket_id, &cli, sizeof(struct client_data));

    printf("Sent to server, waiting for response from server...");
    printf("Sleeping for 5 seconds.\n");
    sleep(5);

    read(socket_id, &ser, sizeof(struct server_data));

    printf("/nServers' response for %s with reg no %ld has arrived.\n", cli.name, cli.regno);
    printf("Student's CGPA is %d and acquired grade is %c\n", ser.cgpa, ser.grade);

    close(socket_id);
}