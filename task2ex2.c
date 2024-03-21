#include <stdio.h>
#include <stdlib.h>

int main() {
    // folosesc apelul system  pentru a executa  comanda ps, pe care o folosesc sa sortez dupa cpu
    //rezultatul comenzi il scriu in fisierul process_list.txt
    system("ps -eo pid,user,%cpu,%mem,comm --sort=-%cpu > process_list.txt");

    // deschid fisierul pentru citire
    FILE *file = fopen("process_list.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // citesc si afisez in consola continutul fisierului
    char line[256]; 
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    // inchid fisierul
    fclose(file);

    return 0;
}
