#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>

int main(){
    switch(fork()){
        case -1: 
            perror("fork failed");
            exit(1);
            break;
        case 0:
            //son
            execlp("./saluta_persone", "saluta_persone", "Pippo", "Pluto", "Paperino", NULL);
            fprintf(stderr, "%s: %d. Error #%03d: %s\n", __FILE__, __LINE__, errno, strerror(errno));
    	    exit(EXIT_FAILURE);
            break;
        default:{
            pid_t childPid;
            int status=0;

            if ((childPid = waitpid(-1, &status, 0))== -1) {
                if (errno == ECHILD) {
                printf("In PID = %d, no more child processes\n",
                        getpid());
                exit(EXIT_SUCCESS);
                } else {
                fprintf(stderr, "Error #%d: %s\n", errno, strerror(errno));
                exit(EXIT_FAILURE);
                }
            }

            if (WIFEXITED(status)) {
                printf("WIFEXITED(status) is true\n");
                printf("WEXITSTATUS(status): %d\n",WEXITSTATUS(status));
            } else {
                printf("Unexpected status\n");
            }

            exit(EXIT_SUCCESS);
        }
            //message = "This is the parent";

            
    }
    return 0;
}