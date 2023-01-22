#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Utilizare: %s nice_value comanda [argumente_comanda]\n", argv[0]);
        return 1;
    }

    char *endptr;
    int n = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Valoarea nice nu este un numar valid\n");
        return 1;
    }
    pid_t pid = fork();
    if (pid < 0) {
        perror("Eroare la crearea procesului copil");
        return 1;
    }
    
    if (pid == 0) {
        int ret = setpriority(PRIO_PROCESS, getpid(), n);
        if (ret < 0) {
            perror("setpriority");
            return 1;
        }
        execvp(argv[2], &argv[2]);

        if(errno) {
            perror("Eroare la execvp");
        }

        if (errno == ENOENT) {
            fprintf(stderr, "Comanda nu a fost gasita\n");
        } 
        else if (errno == EACCES) {
            fprintf(stderr, "Nu aveti permisiunea de a executa aceasta comanda\n");
        } 
        else {
            perror("Eroare la execvp");
        }
        return 1;
    }
    else {
        int status;
        waitpid(pid, &status, 0);
        if(status != 0) {
            printf("Comanda nu s-a putut executa. Cod eroare: %d\n", status);
        }
    }
    return 0;
}