#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int id;
    int pok = 0;
    printf("Proces macierzysty: UID = %d, GID= %d, PID= %d, PGID = %d, PPID = %d \n \n", getuid(), getgid(), getpid(), getpgid(getpid()), getppid());
    for(int i = 0; i < 3; i++){
        id = fork();
        switch(id){
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                pok++;
                printf("Pokolenie nr. %d\n",pok);
                printf("Proces potomny: UID = %d, GID= %d, PID= %d, PGID = %d, PPID = %d \n", getuid(), getgid(), getpid(), getpgid(getpid()), getppid());
                sleep(i);
                break;
            default:
                break;
        }
    }
    sleep(4);
    return 0;
}
