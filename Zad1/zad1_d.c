#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int pot_PID;
    int siur = 0;
    printf("Proces macierzysty: UID = %d, GID= %d, PID= %d, PGID = %d, PPID = %d \n", getuid(), getgid(), getpid(), getpgid(getpid()), getppid());
    for(int i = 0; i < 3; i++){
        pot_PID = fork();
        switch(pot_PID){
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                siur++;
                printf("Proces potomny: UID = %d, GID= %d, PID= %d, PGID = %d, PPID = %d \n", getuid(), getgid(), getpid(), getpgid(getpid()), getppid());
                sleep(4-i);
                printf("%d \n",siur);
                break;
            default:
                sleep(3-i);
                break;
        }
    }
    return 0;
}