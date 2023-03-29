#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

void custom_sighandler(int sig){
    printf("Użyto własnej obsługi sygnału %d\n", sig);
    printf("ID procesu = %d\n", getpid());
}

int main(int argc, char *argv[]){  
    if(argc != 3){
        printf("Nie podano nr. sygnału i sposobu obsługi sygnału.\n");
        exit(EXIT_FAILURE);
    }
    int signal_number = atoi(argv[1]);
    int signal_action = atoi(argv[2]);

    if(signal_action != 1 && signal_action != 2 && signal_action != 3){
        printf("Podano nie prawidłowy sposób obsługi. Przewidywane sposoby to 1, 2 lub 3. \n");
        exit(EXIT_FAILURE);
    }

    char *signal_name = strsignal(signal_number);

    if(signal_action == 1){
        printf("Użyto domyślnej obsługi sygnału %s\n", signal_name);
        if(signal(signal_number, SIG_DFL) == SIG_ERR){
            printf("Funkcja signal ma problem z %s \n", signal_name);
            exit(EXIT_FAILURE);
        }
    }
    if(signal_action == 2){
        printf("Użyto ignorowania sygnału %s\n", signal_name);
        if(signal(signal_number, SIG_IGN) == SIG_ERR){
            printf("Funkcja signal ma problem z %s \n", signal_name);
            exit(EXIT_FAILURE);
        }
    }
    if(signal_action == 3){
        if(signal(signal_number, custom_sighandler) == SIG_ERR){
            printf("Funkcja signal ma problem z %s \n", signal_name);
            exit(EXIT_FAILURE);
        }
    }

    pause();
    return 0;
    
}