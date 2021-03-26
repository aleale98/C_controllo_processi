#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>

#define NUM_KIDS 20

int main(){
    for(int i = 0; i < NUM_KIDS; i++){
        switch(fork()){
            case -1:
                printf("Error\n");
                exit(-1);
                break;
            case 0: //child
                srand(getpid());
                int random_calculated = rand()%6+1;
                printf("%d\n", random_calculated);
			    exit(random_calculated);
                break;
        }
    }
    int status;
    int sum = 0; 
    while (waitpid(-1, &status, 0) != -1)
    {
        sum = sum + WEXITSTATUS(status); 
    }
    printf("Num kids = %u\n", NUM_KIDS);
    printf("Sum calculated: %d\n", sum);
    exit(EXIT_SUCCESS);
}