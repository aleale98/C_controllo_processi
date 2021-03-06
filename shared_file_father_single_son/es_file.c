/*
scrivere un programma in cui un padre e un figlio condividono un file aperto:
 il figlio modifica il file e il padre,
  dopo avere atteso la terminazione del figlio, stampa a video il contenuto del file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include <string.h>

#define MAXCHAR 10

int main(){
    FILE *fp = fopen("shared.txt", "r+");
    
    pid_t figlio = fork();
    switch (figlio)
    {
    case -1:
      printf("Something went wrong!");
      exit(-1);
      break;
    case 0: 
    for(int i = 0; i < 5; i++){
        fprintf(fp,"%s", "Ciao\n");
    }
    exit(1);
    break;
    default:
    printf("Waiting son\n");
    int status;
      wait(&status);
      printf("End wait\n");
      char buf[MAXCHAR];
      fseek(fp, 0, SEEK_SET);
      while (fscanf(fp, "%[^\n] ", buf) != EOF) {
        printf("> %s\n", buf);
    }
    fclose(fp);
    }
    return 0;
}
