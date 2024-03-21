#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>


#define BUF_SIZE 1024

void print_process_info(const char *pid) {
    char path[BUF_SIZE];
    char buffer[BUF_SIZE];
    int fd;
    ssize_t bytes_read;
    
    // Construim calea catre fisierul status
    snprintf(path, sizeof(path), "/proc/%s/status", pid);

    fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    // Citim continutul fisierului status
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return;
    }
    buffer[bytes_read] = '\0';

    // Extragem informatiile necesare
    char *line = strtok(buffer, "\n");
    while (line != NULL) {
        // Comparam doar inceputul liniei pentru a identifica campurile necesare
        if (strncmp(line, "Name:", 5) == 0 || 
            strncmp(line, "Pid:", 4) == 0 || 
            strncmp(line, "PPid:", 5) == 0 ||
            strncmp(line, "Uid:", 4) == 0 ||
            strncmp(line, "Gid:", 4) == 0) {
            printf("%s\n", line);
        }
        line = strtok(NULL, "\n");
    }

    close(fd);
}

int main() {
    DIR *proc_dir = opendir("/proc");
    struct dirent *entry;
    
    if (proc_dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    // Citim intrarile din directorul /proc
    while ((entry = readdir(proc_dir)) != NULL) {
        if (entry->d_type == DT_DIR && isdigit(entry->d_name[0])) {
            // Numele directorului este un numar, deci este PID-ul unui proces
            print_process_info(entry->d_name);
            printf("\n");
        }
    }

    closedir(proc_dir);
    return EXIT_SUCCESS;
}

