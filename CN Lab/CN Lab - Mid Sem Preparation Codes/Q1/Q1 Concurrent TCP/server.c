#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>

#define PORTNO 10478

void handle_client(int new_socket_id) {
    int arr[3][3], buff[3][3];

    read(new_socket_id, arr, sizeof(arr));

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            buff[i][j] = arr[j][i];
        }
    }

    write(new_socket_id, buff, sizeof(buff));

    close(new_socket_id);
}

int main() {
    int socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_id == -1) {
        perror("Socket not created...\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serveraddress;
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddress.sin_port = htons(PORTNO);

    if (bind(socket_id, (struct sockaddr*)&serveraddress, sizeof(serveraddress)) < 0) {
        perror("Bind failed...\n");
        exit(EXIT_FAILURE);
    }

    listen(socket_id, 5);

    signal(SIGCHLD, SIG_IGN);

    printf("Server running...\n");

    while (1) {
        struct sockaddr_in clientaddress;
        socklen_t clilen = sizeof(clientaddress);

        int new_socket_id = accept(socket_id, (struct sockaddr*)&clientaddress, &clilen);
        if (new_socket_id < 0) {
            perror("Accept failed...\n");
            continue;
        }

        pid_t pid = fork();
        if (pid == 0) {
            close(socket_id);
            handle_client(new_socket_id);
            exit(0);
        } else if (pid > 0) {
            close(new_socket_id);
        } else {
            perror("Fork failed...\n");
            close(new_socket_id);
        }
    }

    close(socket_id);
    return 0;
}
