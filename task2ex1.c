#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROCESS_COUNT 7

int main() {
    pid_t pids[PROCESS_COUNT];
    int i;

    // cream procese copil (atatea cate sunt specificate in PROCESS_COUNT).
    for (i = 0; i < PROCESS_COUNT; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("Fork nu s-a putut executa");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0) { // procesul copil
            if (i == 2) {
                // verificam daca procesul e procesul numarul 3
                sleep(2);
                printf("Procesul copil numarul(PID %d) s-a executat.\n", getpid());
                exit(0);
            } else {
                // daca sunt alte procese in afara de proceul 3, ele intra in intr-un loop infinit unde asteapta semnalul de kill
                
                while (1) {
                    sleep(1); 
                }
            }
        }
    }

    // procesul parinte asteapta dupa semnalul de exit de la procesul 3
    int status;
    waitpid(pids[2], &status, 0);
    printf("Procesul 3 si-a terminat executia, se trimit semnale catre restul proceselor\n");

    // aici trimit mesaje catre retul proceselor care nu sunt procesul 3
    for (i = 0; i < PROCESS_COUNT; i++) {
        if (i != 2) { 
            kill(pids[i], SIGTERM);
            printf("Semnalul SIGTERM a fost trimis catre procesul copil%d (PID %d).\n", i + 1, pids[i]);
        }
    }

    // astempt toate procesele sa isi termine executia inainte de parine
    while (wait(NULL) > 0);

    printf("Procesul parinte si-a terminat executia\n");
    return 0;
}
