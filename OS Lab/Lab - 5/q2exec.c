#include "include.h"
int main(){
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        fprintf(stderr,"Fork Failed");
        exit(-1);
    }
    else if(pid == 0){
        execlp("./q1blockparent", "q1blockparent", NULL); 
    }
    else{
        wait (NULL);
        write(1,"Complete\n",10);
        exit(0);
    }
}