#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

void create_child_processes(int numProcesses) {
    printf("Proces[B] PID %d PPID %d\n", getpid(), getppid()); // B process
    for (int i = 0; i < numProcesses; ++i) {
        pid_t pid = fork();
        if (pid == 0) { // Child process
            printf("Proces[%d] PID %d PPID %d\n", i, getpid(), getppid());
            // Last child does not create a new process
            if (i < numProcesses - 1) {
                continue;
            } else {
                exit(0);
            }
        } else if (pid > 0) {
            wait(NULL); // Wait for the child to finish
            break; // Parent (B) does not need to loop
        } else {
            fprintf(stderr, "Failed to fork: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3 || (strcmp(argv[1], "-p") != 0 && strcmp(argv[1], "--processes") != 0)) {
        fprintf(stderr, "Usage: %s -p <numProcesses> OR %s --processes <numProcesses>\n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    int numProcesses = atoi(argv[2]);
    if (numProcesses < 1) {
        fprintf(stderr, "Error: The number of processes must be at least 1.\n");
        return EXIT_FAILURE;
    }

    printf("Proces[A] PID %d PPID %d\n", getpid(), getppid()); // A process
    pid_t pidB = fork();
    if (pidB == 0) {
        create_child_processes(numProcesses); // B creates child processes
        exit(0); // B process exits after children are done
    } else if (pidB > 0) {
        wait(NULL); // A waits for B to finish
    } else {
        fprintf(stderr, "Failed to fork: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    return 0;
}

