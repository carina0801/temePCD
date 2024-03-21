#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void create_subprocesses(int num_subprocesses, int level) {
    pid_t pid;
    int i;
    for (i = 1; i <= num_subprocesses; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            printf("Proces[%d.%d] PID %d PPID %d\n", level, i, getpid(), getppid());
            exit(EXIT_SUCCESS);
        } else {
            // Parent process
            wait(NULL); // Wait for child process to finish
        }
    }
}

int main(int argc, char *argv[]) {
    int processes = 0, subprocesses = 0;
    pid_t pid;
    int i;

    // Parse arguments for number of processes and subprocesses
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--processes") == 0 || strcmp(argv[i], "-p") == 0) {
            processes = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--subprocesses") == 0 || strcmp(argv[i], "-s") == 0) {
            subprocesses = atoi(argv[++i]);
        }
    }

    printf("Proces[A] PID %d PPID %d\n", getpid(), getppid());
    pid = fork();

    if (pid == -1) {
        // Fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child B
        printf("Proces[B] PID %d PPID %d\n", getpid(), getppid());
        pid = fork();

        if (pid == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child 0
            printf("Proces[0] PID %d PPID %d\n", getpid(), getppid());
            for (i = 1; i <= processes; i++) {
                pid = fork();

                if (pid == -1) {
                    perror("fork failed");
                    exit(EXIT_FAILURE);
                } else if (pid == 0) {
                    // Child process i
                    printf("Proces[%d] PID %d PPID %d\n", i, getpid(), getppid());
                    create_subprocesses(subprocesses, i);
                    exit(EXIT_SUCCESS);
                } else {
                    wait(NULL); // Wait for child process to finish
                }
            }
        } else {
            wait(NULL); // Wait for child 0 to finish
        }
    } else {
        wait(NULL); // Wait for child B to finish
    }

    return EXIT_SUCCESS;
}

