#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int UID = getuid();
    int GID = getgid();
    int PID = getpid();
    int PPID = getppid();
    int PGID = getpgid(PID);

    printf("UID = %d \n",UID);
    printf("GID = %d \n",GID);
    printf("PID = %d \n",PID);
    printf("PPID = %d \n",PPID);
    printf("PGID = %d \n",PGID);
    return 0;
}
