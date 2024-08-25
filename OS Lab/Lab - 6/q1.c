#include"headers.h"
int main() {
    int pipe_fd, res,j, O_RDONLY, buffer[BUFFER_SIZE+1], bytes_read = 0;
    printf("Process %d opening FIFO O_RDONLY\n",getpid());
    pipe_fd = open(FIFO_NAME,open_mode);
    printf("Process %d result %d\n",getpid(),pipe_fd);
    if(pipe_fd != -1){
        printf("The numbers are\n");
        for(j=0;j<5;j++){
            res = read(pipe_fd,&buffer[j],sizeof(buffer[0]));
            printf("%d\t",buffer[j]);
        }
        bytes_read+=res;
    }
    else{
        exit(EXIT_FAILURE);
    }
    printf("\nProcess %d finished %d bytes read\n",getpid(),bytes_read);
    exit(EXIT_SUCCESS);
}
