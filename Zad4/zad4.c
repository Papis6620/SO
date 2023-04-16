#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<string.h>

#define BUFFER_SIZE 10

int main(){

    int filedes[2];
    unsigned char buffer[BUFFER_SIZE];
    int id;

    if(pipe(filedes) == -1){    //tworzenie potoku
        perror("pipe error: ");
        exit(EXIT_FAILURE);
    }
    
    id = fork();
    if(id == -1){
        perror("fork error: ");
        exit(EXIT_FAILURE);
    }

    if(id > 0){ // producent
        close(filedes[0]);
        int plik = open("plik", O_RDONLY, 0666);
        int odczyt;
        int zapis;
        if(plik == -1){
            perror("open error: ");
            exit(EXIT_FAILURE);
        }
        while((odczyt = read(plik,buffer,BUFFER_SIZE)) > 0){
            if((zapis = write(filedes[1], buffer, odczyt)) > 0){
                printf("Przesłano %s (%d bajtów)\n", buffer, zapis);
            }else if(zapis == -1){
                perror("write error: ");
                exit(EXIT_FAILURE);
            }
            memset(buffer, 0, BUFFER_SIZE);
        }
        close(plik);
        close(filedes[1]);
        wait(NULL);

    }else{
        close(filedes[1]);
        int plik2 = open("output", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        int odczyt;
        int zapis;
        if(plik2 == -1){
            perror("open error: ");
            exit(EXIT_FAILURE);
        }
        while((odczyt = read(filedes[0],buffer,BUFFER_SIZE)) > 0){
            if((zapis = write(plik2, buffer, odczyt)) > 0){
                printf("Pobrano %s (%d bajtów)\n", buffer, zapis);
            }else if(zapis == -1){
                perror("write error: ");
                exit(EXIT_FAILURE);
            }
            memset(buffer, 0, BUFFER_SIZE);
        }
        close(plik2);
        close(filedes[0]);
    }

    return 0;


}